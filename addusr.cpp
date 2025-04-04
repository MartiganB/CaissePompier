#include "addusr.h"
#include "ui_addusr.h"
#include "gestionmenu.h"
#include <QDir>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>

AddUsr::AddUsr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddUsr)
{
    ui->setupUi(this);
    showFullScreen();
}

AddUsr::~AddUsr()
{
    delete ui;
}

void AddUsr::on_pushButton_val_clicked()
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
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString usr = ui->lineEdit_usr->text();
    QString pwd = ui->lineEdit_pwd->text();
    QString droit = ui->comboBox_droit->currentText();

    // Exécuter une requête paramétrée pour éviter les injections SQL
    QSqlQuery query;
    if(usr!="" && pwd!="")
    {
        query.prepare("INSERT INTO gerants (nom, prenom, username, password, droit) " "VALUES (:nom, :prenom, :usr, :pwd, :droit)");
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":usr", usr);
        query.bindValue(":pwd", pwd);
        query.bindValue(":droit", droit);
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Aucun nom d'utilisateur ni mot de passe enregistrer");
    }


    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion : " << query.lastError();
    } else {
        qDebug() << "Insertion réussie.";
        QMessageBox::information(this, "Succès", "Utilisateur ajouté avec succès !");
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->lineEdit_usr->clear();
        ui->lineEdit_pwd->clear();
    }
}


void AddUsr::on_pushButton_back_clicked()
{
    GestionMenu *gestion = new GestionMenu();
    gestion->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    gestion->setWindowTitle("Gestion");
    gestion->show();
    db.close();
    this->close();
}





void AddUsr::on_checkBox_print_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked) ui->lineEdit_pwd->setEchoMode(QLineEdit::Normal);
    else ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
}

