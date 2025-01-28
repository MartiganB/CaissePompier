#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Permet de donner un nom à l'onglet
    setWindowTitle("Caisse - [CSP]");

    //Permet d'empecher l'utilisateur de cliquer sur l'objet
    ui->textEdit_EAN->setDisabled(true);
    ui->textEdit_DerArticle->setDisabled(true);
    ui->textEdit_Carte->setDisabled(true);
    ui->textEdit_AffPrix->setDisabled(true);
    ui->tableView_Articles->setDisabled(true);

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

    //Permet de lier le bouton a une fonction
    connect(ui->pushButton_Valider, &QPushButton::clicked, this, &MainWindow::verifierEAN);

    ui->tableView_Articles->verticalHeader()->setVisible(false);

    ui->textEdit_AffPrix->setText("0€");

    // Modèle avec 3 colonnes et plusieurs lignes
    QStandardItemModel *model = new QStandardItemModel(0, 3, this);
    model->setHeaderData(0, Qt::Horizontal, "Qte");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prix");


    ui->tableView_Articles->setModel(model);
    ui->tableView_Articles->setColumnWidth(0,50);
    ui->tableView_Articles->setColumnWidth(1,610);
    ui->tableView_Articles->setColumnWidth(2,125);
    //ui->tableView_Articles->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verifierEAN()
{
    QString content = ui->textEdit_EAN->toPlainText();

    //Cherche si il y a un "x" dans textEdit_EAN
    int xIndex = content.indexOf("x", Qt::CaseInsensitive);
    QString valeurAvantX;
    if (xIndex == -1) {
        qDebug() << "Aucun 'x' trouvé dans l'entrée";
        valeurAvantX = "1";
    }
    else
    {
        valeurAvantX = content.left(xIndex).trimmed();
    }

    // Récupérer le code EAN après "x"
    QString codeEAN = content.mid(xIndex + 1).trimmed();

    // Vérifier que le champ n'est pas vide et contient uniquement des chiffres
    if (codeEAN.isEmpty() || !codeEAN.contains(QRegularExpression("^[0-9]+$"))) {
        qDebug() << "EAN invalide ou vide : " << codeEAN;
        ui->textEdit_EAN->clear();
        return;
    }

    // Vérifier si le produit existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT Nom, Prix, Quantite FROM articles WHERE EAN = :ean");
    query.bindValue(":ean", codeEAN);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        ui->textEdit_EAN->clear();
        return;
    }

    // Vérifier si on a trouvé un produit
    if (query.next()) {
        QString nom = query.value(0).toString();
        double prix = query.value(1).toDouble();
        QString quantite = valeurAvantX;
        qDebug() << "Produit trouvé : Nom =" << nom << ", Prix =" << prix << "€, Quantité =" << quantite;

        // Affichage dans les widgets
        ui->textEdit_DerArticle->setText(nom);
        //ui->textEdit_AffPrix->setText(QString::number(prix) + "€");

        // Ajouter au tableau si non présent, sinon incrémenter la quantité
        QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->tableView_Articles->model());
        if (!model) return;

        QString ancienPrix = ui->textEdit_AffPrix->toPlainText();

        int enlvEuro = ancienPrix.indexOf("€", Qt::CaseInsensitive);
        QString valeurAvantEuro = ancienPrix.left(enlvEuro).trimmed();

        double tt = prix * quantite.toDouble();
        double ancienPrixDouble = tt+valeurAvantEuro.toDouble();

        QList<QStandardItem *> newRow;
        newRow.append(new QStandardItem(quantite)); // Quantité
        newRow.append(new QStandardItem(nom)); // Nom
        newRow.append(new QStandardItem(QString::number(tt, 'f', 2) + "€"));
        model->appendRow(newRow);
        ui->tableView_Articles->scrollToBottom();

        ui->textEdit_AffPrix->setText(QString::number(ancienPrixDouble, 'f', 2) + "€");
        // Effacer le champ EAN après ajout
        ui->textEdit_EAN->clear();
    } else {
        qDebug() << "Produit non trouvé pour EAN :" << codeEAN;
        ui->textEdit_AffPrix->clear();
        ui->textEdit_EAN->clear();
        ui->textEdit_DerArticle->setText("Produit non trouvé.");
    }
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->textEdit_EAN->insertPlainText("1");
    //qDebug() << "1";
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit_EAN->insertPlainText("2");
    //qDebug() << "2";
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit_EAN->insertPlainText("3");
    //qDebug() << "3";
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit_EAN->insertPlainText("4");
    //qDebug() << "4";
}
void MainWindow::on_pushButton_5_clicked()
{
    ui->textEdit_EAN->insertPlainText("5");
    //qDebug() << "5";
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit_EAN->insertPlainText("6");
    //qDebug() << "6";
}
void MainWindow::on_pushButton_7_clicked()
{
    ui->textEdit_EAN->insertPlainText("7");
    //qDebug() << "7";
}
void MainWindow::on_pushButton_8_clicked()
{
    ui->textEdit_EAN->insertPlainText("8");
    //qDebug() << "8";
}
void MainWindow::on_pushButton_9_clicked()
{
    ui->textEdit_EAN->insertPlainText("9");
    //qDebug() << "9";
}
void MainWindow::on_pushButton_0_clicked()
{
    ui->textEdit_EAN->insertPlainText("0");
    //qDebug() << "0";
}
void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textEdit_EAN->clear();
    //qDebug() << "Clear";
}
void MainWindow::on_pushButton_virgule_clicked()
{
    ui->textEdit_EAN->insertPlainText(",");
    //qDebug() << ",";
}
void MainWindow::on_pushButton_Valider_clicked()
{

}
void MainWindow::on_pushButton_Multiplier_clicked()
{
    ui->textEdit_EAN->insertPlainText("x");
    //qDebug() << "x";
}

void MainWindow::on_pushButton_Suppr_clicked()
{
    QTextCursor cursor = ui->textEdit_EAN->textCursor();
    //Place le curseur a la fin du textEdit_EAN
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    // Supprime le caractère avant le curseur
    cursor.deletePreviousChar();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString text = ui->textEdit_EAN->toPlainText();
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        ui->textEdit_EAN->clear(); // Efface le texte
    }

    qDebug() << text;
    ui->textEdit_EAN->setPlainText(text + event->text());
}

void MainWindow::on_textEdit_EAN_textChanged()
{
    if (ui->textEdit_EAN->toPlainText().endsWith("\n")) {
        verifierEAN();
        ui->textEdit_EAN->clear();
    }
}
