#include "menustock.h"
#include "ui_menustock.h"
#include "menu.h"

MenuStock::MenuStock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuStock)
{
    ui->setupUi(this);
    showFullScreen();
}

MenuStock::~MenuStock()
{
    delete ui;
}

void MenuStock::on_commandLinkButton_add_clicked()
{
    addStock = new AddStock();
    addStock->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    addStock->setWindowTitle("Ajouter un produit");
    addStock->show();
    this->close();
}

void MenuStock::on_commandLinkButton_del_clicked()
{
    delStock = new DelStock();
    delStock->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    delStock->setWindowTitle("Supprimer un produit");
    delStock->show();
    this->close();
}

void MenuStock::on_commandLinkButton_change_clicked()
{
    modStock = new ModStock();
    modStock->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    modStock->setWindowTitle("Modifier un produit");
    modStock->show();
    this->close();
}




void MenuStock::on_pushButton_back_clicked()
{
    Menu *menu = new Menu();
    menu->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    menu->setWindowTitle("Menu");
    menu->show();
    this->close();
}
