#include "modstock.h"
#include "ui_modstock.h"
#include "menustock.h"

ModStock::ModStock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ModStock)
{
    ui->setupUi(this);
    showFullScreen();
}

ModStock::~ModStock()
{
    delete ui;
}

void ModStock::on_pushButton_back_clicked()
{
    MenuStock *stock = new MenuStock();
    stock->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    stock->setWindowTitle("Stock");
    stock->show();
    db.close();
    this->close();
}

