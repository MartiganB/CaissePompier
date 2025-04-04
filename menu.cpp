#include "menu.h"
#include "connexion.h"
#include "qevent.h"
#include "ui_menu.h"
#include "gestionmenu.h"
#include <QDir>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    //qDebug() << "Ouverture fenetre menu";
    ui->setupUi(this);
    showFullScreen();
}

Menu::~Menu()
{
    //qDebug() << "Delete fenetre menu";
    delete ui;
}

void Menu::on_pushButton_deco_clicked()
{
    ui->commandLinkButton_admin->setEnabled(true);
    ui->commandLinkButton_stock->setEnabled(true);
    ui->commandLinkButton_caisse->setEnabled(true);

    // Ouvrir la fenêtre de connexion
    connexion *login = new connexion();
    login->show();
    this->close();
}

void Menu::closeEvent(QCloseEvent *event)
{
    //qDebug() << "QCloseEvent Menu" ;
    event->accept();
    deleteLater();
}


void Menu::on_commandLinkButton_admin_clicked()
{
    // Ouvrir le menu
    gestMenu = new GestionMenu();
    gestMenu->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    gestMenu->setWindowTitle("Gestion");
    gestMenu->show();
    this->close();
}


void Menu::on_commandLinkButton_caisse_clicked()
{
    caisse = new MainWindow();
    caisse->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    caisse->setWindowTitle("Caisse");
    caisse->show();
    this->close();
}


void Menu::on_commandLinkButton_stock_clicked()
{
    menuStock = new MenuStock();
    menuStock->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    menuStock->setWindowTitle("Stock");
    menuStock->show();
    this->close();
}

