#include "gestionmenu.h"
#include "ui_gestionmenu.h"
#include "menu.h"
#include <QDir>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>

GestionMenu::GestionMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionMenu)
{
    ui->setupUi(this);
    showFullScreen();
}

GestionMenu::~GestionMenu()
{
    delete ui;
}

void GestionMenu::on_commandLinkButton_add_clicked()
{
    addUsr = new AddUsr();
    addUsr->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    addUsr->setWindowTitle("Ajouter un utilisateur");
    addUsr->show();
    this->close();
}

void GestionMenu::on_commandLinkButton_del_clicked()
{
    delUsr = new DelUsr();
    delUsr->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    delUsr->setWindowTitle("Supprimer un utilisateur");
    delUsr->show();
    this->close();
}

void GestionMenu::on_commandLinkButton_change_clicked()
{
    modUsr = new ModUsr();
    modUsr->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    modUsr->setWindowTitle("Modifier un utilisateur");
    modUsr->show();
    this->close();
}

void GestionMenu::closeEvent(QCloseEvent *event)
{
    event->accept();
    deleteLater();
}


void GestionMenu::on_pushButton_back_clicked()
{
    Menu *menu = new Menu();
    menu->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    menu->setWindowTitle("Menu");
    menu->show();
    this->close();
}






