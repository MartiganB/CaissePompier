#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextBrowser"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Permet de donner un nom à l'onglet
    setWindowTitle("Caisse - [CSP]");

    //Connexion à la base de donnée en local
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("projetpompier");
    db.setUserName("root");
    db.setPassword("");
    db.setPort(3306);
    if (!db.open()) {
        qWarning() << "Erreur de connexion a la base de donnees:" << db.lastError().text();
    }
    else
    {
        qDebug() << "Connexion a la base de donnees reussie";
    }
    connect(ui->pushButton_Valider, &QPushButton::clicked, this, &MainWindow::verifierEAN);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verifierEAN()
{
    QString content = ui->textBrowser_EAN->toPlainText();

    //Cherche si il y a un "x" dans textBrowser_EAN
    int xIndex = content.indexOf("x", Qt::CaseInsensitive);
    if (xIndex == -1) {
        qDebug() << "Aucun 'x' trouvé dans l'entrée";
    }

    // Récupérer le code EAN après "x"
    QString codeEAN = content.mid(xIndex + 1).trimmed();

    // Vérifier que le champ n'est pas vide et contient uniquement des chiffres
    if (codeEAN.isEmpty() || !codeEAN.contains(QRegularExpression("^[0-9]+$"))) {
        qDebug() << "EAN invalide ou vide : " << codeEAN;
        ui->textBrowser_EAN->clear();
        return;
    }

    // Vérifier si le produit existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT Nom, Prix, Quantite FROM articles WHERE EAN = :ean");
    query.bindValue(":ean", codeEAN);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        ui->textBrowser_EAN->clear();
        return;
    }

    // Vérifier si on a trouvé un produit
    if (query.next()) {
        QString nom = query.value(0).toString();
        QString prix = query.value(1).toString();
        QString quantite = query.value(2).toString();

        qDebug() << "Produit trouvé : Nom =" << nom << ", Prix =" << prix << "€, Quantité =" << quantite;

        // Affichage dans un widget par exemple
        ui->textBrowser_DerArticle->setText(QString(nom));
        ui->textBrowser_AffPrix->setText(QString(prix)+"€");
        ui->textBrowser_EAN->clear();
    } else {
        qDebug() << "Produit non trouvé pour EAN :" << codeEAN;
        ui->textBrowser_EAN->setText("Produit non trouvé.");
        ui->textBrowser_EAN->clear();
    }
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->textBrowser_EAN->insertPlainText("1");
    //qDebug() << "1";
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser_EAN->insertPlainText("2");
    //qDebug() << "2";
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser_EAN->insertPlainText("3");
    //qDebug() << "3";
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textBrowser_EAN->insertPlainText("4");
    //qDebug() << "4";
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser_EAN->insertPlainText("5");
    //qDebug() << "5";
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->textBrowser_EAN->insertPlainText("6");
    //qDebug() << "6";
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser_EAN->insertPlainText("7");
    //qDebug() << "7";
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->textBrowser_EAN->insertPlainText("8");
    //qDebug() << "8";
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->textBrowser_EAN->insertPlainText("9");
    //qDebug() << "9";
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->textBrowser_EAN->insertPlainText("0");
    //qDebug() << "0";
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textBrowser_EAN->clear();
    //qDebug() << "Clear";
}

void MainWindow::on_pushButton_virgule_clicked()
{
    ui->textBrowser_EAN->insertPlainText(",");
    //qDebug() << ",";
}

void MainWindow::on_pushButton_Valider_clicked()
{
    //QString content = ui->textBrowser_EAN->toPlainText();
    //connect(ui->pushButton_Valider, &QPushButton::clicked, this, &MainWindow::verifierEAN);
}


void MainWindow::on_pushButton_Multiplier_clicked()
{
    ui->textBrowser_EAN->insertPlainText("x");
    //qDebug() << "x";
}


void MainWindow::on_pushButton_Suppr_clicked()
{
    QTextCursor cursor = ui->textBrowser_EAN->textCursor();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    cursor.deletePreviousChar(); // Supprime le caractère avant le curseur

}

