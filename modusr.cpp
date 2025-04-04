#include "modusr.h"
#include "ui_modusr.h"
#include "gestionmenu.h"
#include <QVariant>

ModUsr::ModUsr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ModUsr)
{
    ui->setupUi(this);
    showFullScreen();
    model = new QStandardItemModel(0, 4, this);  // Notez que nous avons maintenant 4 colonnes
    model->setHeaderData(0, Qt::Horizontal, "Nom");
    model->setHeaderData(1, Qt::Horizontal, "Prenom");
    model->setHeaderData(2, Qt::Horizontal, "Droit");
    model->setHeaderData(3, Qt::Horizontal, "Modifier Droit");

    ui->tableView_user->setModel(model);
    ui->tableView_user->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_user->setColumnWidth(0, 242);
    ui->tableView_user->setColumnWidth(1, 243);
    ui->tableView_user->setColumnWidth(2, 242);
    ui->tableView_user->setColumnWidth(3, 243);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.2");
    db.setDatabaseName("foyer");
    db.setUserName("user");
    db.setPassword("okokok");

    if (!db.open()) {
        qDebug() << "Erreur : échec de la connexion à la BDD." << db.lastError();
    } else {
        qDebug() << "Connexion réussie.";
    }

    QSqlQuery query("SELECT Nom, Prenom, droit FROM gerants");

    int row = 0;
    while (query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QString droit = query.value(2).toString();

        model->insertRow(row);
        model->setData(model->index(row, 0), nom);
        model->setData(model->index(row, 1), prenom);
        model->setData(model->index(row, 2), droit);

        comboBox_droit = new QComboBox();
        comboBox_droit->addItem("admin");
        comboBox_droit->addItem("caisse");
        comboBox_droit->addItem("stock");

        //qDebug()<<"droit";
        if(prenom!="admin" && prenom!="stock" && prenom!="caisse")
        {
            // Définit la valeur actuelle de la combo box
            comboBox_droit->setCurrentText(droit);
            comboBox_droit->setProperty("droit", droit);
            comboBox_droit->setProperty("row", row);
            connect(comboBox_droit, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ModUsr::handleComboBoxIndexChanged);

            //qDebug()<<"Après fonction";

            ui->tableView_user->setIndexWidget(model->index(row, 3), comboBox_droit);
        }


        row++;
    }
}

ModUsr::~ModUsr()
{
    delete ui;
}

void ModUsr::on_pushButton_back_clicked()
{
    GestionMenu *gestion = new GestionMenu();
    gestion->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    gestion->setWindowTitle("Gestion");
    gestion->show();
    this->close();
}

void ModUsr::handleComboBoxIndexChanged() {
    //qDebug()<<"Fonction debut";
    comboBox_droit = qobject_cast<QComboBox *>(sender());
    if (comboBox_droit) {
        int row = comboBox_droit->property("row").toInt();
        QString newDroit = comboBox_droit->currentText();

        // Mettez à jour le modèle avec la nouvelle valeur
        model->setData(model->index(row, 2), newDroit);

        // Optionnel : Mettez à jour la base de données avec la nouvelle valeur
        QString nom = model->data(model->index(row, 0)).toString();
        QString prenom = model->data(model->index(row, 1)).toString();

        QSqlQuery query;
        query.prepare("UPDATE gerants SET droit = :droit WHERE nom = :nom AND prenom = :prenom");
        query.bindValue(":droit", newDroit);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);

        //qDebug()<<"Fonction fin";

        if (query.exec()) {
            qDebug() << "Droit mis à jour pour" << nom << prenom;
        } else {
            qDebug() << "Échec de la mise à jour du droit pour" << nom << prenom << ":" << query.lastError();
        }
    }
}

