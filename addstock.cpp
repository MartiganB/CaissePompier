#include "addstock.h"
#include "ui_addstock.h"
#include "menustock.h"

AddStock::AddStock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddStock)
{
    ui->setupUi(this);
    showFullScreen();
}

AddStock::~AddStock()
{
    delete ui;
}

void AddStock::on_pushButton_back_clicked()
{
    MenuStock *stock = new MenuStock();
    stock->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    stock->setWindowTitle("Stock");
    stock->show();
    db.close();
    this->close();
}

