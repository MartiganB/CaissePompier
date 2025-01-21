#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextBrowser"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->textBrowser_EAN->insertPlainText("1");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser_EAN->insertPlainText("2");
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser_EAN->insertPlainText("3");
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->textBrowser_EAN->insertPlainText("4");
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser_EAN->insertPlainText("5");
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->textBrowser_EAN->insertPlainText("6");
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser_EAN->insertPlainText("7");
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->textBrowser_EAN->insertPlainText("8");
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->textBrowser_EAN->insertPlainText("9");
}


void MainWindow::on_pushButton_0_clicked()
{
    ui->textBrowser_EAN->insertPlainText("0");
}


void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textBrowser_EAN->clear();
}


void MainWindow::on_pushButton_virgule_clicked()
{
    ui->textBrowser_EAN->insertPlainText(",");
}


void MainWindow::on_pushButton_Valider_clicked()
{

    QString content = ui->textBrowser_EAN->toPlainText();

    // Trouver la position du premier "x" dans le texte
    int xIndex = content.indexOf("x", Qt::CaseInsensitive);

    if (xIndex != -1) {
        QString multipl = content.left(xIndex);
        qDebug() << "Multiplie par : " << multipl;
        QString EAN = content.mid(xIndex+1);
        qDebug() << "EAN : " << EAN;
    } else {
        // Si "x" n'est pas trouvé, faire autre chose
        qDebug() << "Le 'x' n'a pas été trouvé dans le texte.";
    }
    ui->textBrowser_EAN->clear();
}


void MainWindow::on_pushButton_Multiplier_clicked()
{
    ui->textBrowser_EAN->insertPlainText("x");
}

