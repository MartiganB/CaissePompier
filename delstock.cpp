#include "delstock.h"
#include "ui_delstock.h"

DelStock::DelStock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DelStock)
{
    ui->setupUi(this);
    showFullScreen();
}

DelStock::~DelStock()
{
    delete ui;
}
