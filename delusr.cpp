#include "delusr.h"
#include "ui_delusr.h"
#include "gestionmenu.h"

DelUsr::DelUsr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DelUsr)
{
    ui->setupUi(this);
    showFullScreen();

    model = new QStandardItemModel(0, 4, this);
    model->setHeaderData(0, Qt::Horizontal, "Nom");
    model->setHeaderData(1, Qt::Horizontal, "Prenom");
    model->setHeaderData(2, Qt::Horizontal, "Nom d'utilisateur");
    model->setHeaderData(3, Qt::Horizontal, "Supprimer");


    ui->tableView_user->setModel(model);
    ui->tableView_user->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_user->setColumnWidth(0,282);
    ui->tableView_user->setColumnWidth(1,282);
    ui->tableView_user->setColumnWidth(2,282);
    ui->tableView_user->setColumnWidth(3,124);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.2");
    db.setDatabaseName("foyer");
    db.setUserName("user");
    db.setPassword("okokok");
    db.setPort(3306);

    if (!db.open()) {
        qDebug() << "Erreur : échec de la connexion à la BDD." << db.lastError();
    } else {
        qDebug() << "Connexion réussie.";
    }

    QSqlQuery query("SELECT Nom, Prenom, username FROM gerants");
    int row = 0;

    while (query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QString usr = query.value(2).toString();

        model->insertRow(row);
        model->setData(model->index(row, 0), nom);
        model->setData(model->index(row, 1), prenom);
        model->setData(model->index(row, 2), usr);

        // Ajout d'une checkbox pour la colonne "Supprimer"
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);

        QCheckBox *checkBox = new QCheckBox();
        layout->addWidget(checkBox);
        widget->setLayout(layout);

        // Connexion du signal stateChanged pour mettre à jour le modèle
        connect(checkBox, &QCheckBox::checkStateChanged, this, [this, row](int state) {
            QModelIndex index = model->index(row, 3);
            //model->setData(index, state == Qt::Checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
            model->setData(index, state == Qt::Checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
        });

        // Vérification et association du widget à la cellule
        if (!ui->tableView_user->indexWidget(model->index(row, 3))) {
            ui->tableView_user->setIndexWidget(model->index(row, 3), widget);
        }

        row++;
    }
}

DelUsr::~DelUsr()
{
    delete ui;
}

void DelUsr::on_pushButton_back_clicked()
{
    db.close();
    GestionMenu *gestion = new GestionMenu();
    gestion->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    gestion->setWindowTitle("Gestion");
    gestion->show();
    this->close();
}

void DelUsr::on_pushButton_del_clicked()
{
    for (int i = 0; i < model->rowCount(); ++i) {
        // Obtenir l'index de la cellule contenant la checkbox
        QModelIndex index = model->index(i, 3);

        // Récupérer l'état de la case à cocher
        QVariant value = model->data(index, Qt::CheckStateRole);

        // Vérifier si la checkbox est cochée
        if (value == Qt::Checked) {
            QModelIndex usernameIndex = model->index(i, 2);
            QString username = model->data(usernameIndex).toString();

            QSqlQuery query;
            query.prepare("DELETE FROM gerants WHERE username = :username");
            query.bindValue(":username", username);

            if (!query.exec()) {
                qDebug() << "Erreur lors de la suppression de l'utilisateur:" << query.lastError();
            } else {
                qDebug() << "Utilisateur" << username << "supprimé avec succès.";
                model->removeRow(i); // Supprimer la ligne du modèle après suppression
                i--; // Ajuster l'index après la suppression
            }
        }
    }
}
