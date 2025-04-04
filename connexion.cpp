#include "connexion.h"
#include "ui_connexion.h"
#include "menu.h"
#include <QDir>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>
#include "ui_menu.h"

connexion::connexion(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::connexion)
    //menu(new Menu(this))
{
    //qDebug() << "Ouverture fenetre connexion";
    ui->setupUi(this);
    showFullScreen();
    setWindowTitle("Foyer");
    setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    QWidget::setTabOrder(ui->lineEdit_usr, ui->lineEdit_pwd);
    QWidget::setTabOrder(ui->lineEdit_pwd, ui->checkBox_print);
    QWidget::setTabOrder(ui->checkBox_print, ui->pushButton_val);
    ui->pushButton_val->setDefault(true);
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(shortcut, &QShortcut::activated, this, &connexion::on_pushButton_val_clicked);
    //ui->
}

connexion::~connexion()
{
    //qDebug() << "Delete fenetre connexion";
    delete ui;
}

void connexion::on_checkBox_print_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked) ui->lineEdit_pwd->setEchoMode(QLineEdit::Normal);
    else ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
}

void connexion::on_pushButton_val_clicked()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.2");
    db.setDatabaseName("foyer");
    db.setUserName("user");
    db.setPassword("okokok");
    db.setPort(3306);

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données : " << db.lastError().text();
        return;
    }

    // Récupérer les valeurs des champs utilisateur
    QString usr = ui->lineEdit_usr->text();
    QString pwd = ui->lineEdit_pwd->text();

    // Exécuter une requête paramétrée pour éviter les injections SQL
    QSqlQuery query;
    query.prepare("SELECT droit FROM gerants WHERE username = :usr AND password = :pwd");
    query.bindValue(":usr", usr);
    query.bindValue(":pwd", pwd);

    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête SQL : " << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString droit = query.value(0).toString();
        qDebug() << "Connexion réussie pour l'utilisateur :" << usr << "avec droit :" << droit;


        // Ouvrir le menu
        menu = new Menu();
        menu->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
        menu->setWindowTitle("Menu");
        menu->show();

        this->close();

        // Désactiver les boutons selon le droit
        if (droit == "caisse") {
            menu->ui->commandLinkButton_admin->setDisabled(true);
            menu->ui->commandLinkButton_stock->setDisabled(true);
        } else if (droit == "stock") {
            menu->ui->commandLinkButton_admin->setDisabled(true);
            menu->ui->commandLinkButton_caisse->setDisabled(true);
        }



    } else {
        QMessageBox::critical(this, "Erreur", "Nom d'utilisateur ou mot de passe incorrect.");
        ui->lineEdit_usr->clear();
        ui->lineEdit_pwd->clear();
    }

    db.close();

}

void connexion::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_pushButton_val_clicked();  // Exécuter la fonction du bouton
    } else {
        QWidget::keyPressEvent(event);  // Passer l'événement au parent
    }
}

void connexion::closeEvent(QCloseEvent *event)
{
    //qDebug() << "QCloseEvent connexion" ;
    event->accept();
    deleteLater();
}




