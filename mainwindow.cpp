#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"

using namespace Qt;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Permet de mettre la caisse en plein ecran
    showFullScreen();

    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_00, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_virgule, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_quantite, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);


    //Permet d'empecher l'utilisateur de cliquer sur l'objet afin d'éditer les informations
    ui->tableView_articles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_articles->verticalHeader()->setVisible(false);
    ui->tableView_articles->setStyleSheet("background-color: white;color: rgb(0, 0, 0);");
    ui->tableView_articles->resetVerticalScrollMode();

    ui->label_prix->setText("0€");

    //Param son de notification erreur
    sound = new QSoundEffect(this);  // Création avec un parent pour éviter les fuites mémoire
    sound->setSource(QUrl::fromLocalFile(QDir::currentPath() +"../../../error.wav"));
    sound->setVolume(100);

    //Connexion à la base de donnée à distance
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.2");
    db.setDatabaseName("foyer");
    db.setUserName("user");
    db.setPassword("okokok");
    db.setPort(3306);

    if (!db.open()) {
        QMessageBox::warning(this, "Base De Donnée", "Un problème a été detecté avec la connexion à la base de donnée");
        qWarning() << "Erreur de connexion à la base de données:" << db.lastError().text();
    } else {
        qDebug() << "Connexion réussie à la base de données.";
    }

    // Modèle avec 3 colonnes et plusieurs lignes
    QStandardItemModel *model = new QStandardItemModel(0, 4, this);
    model->setHeaderData(0, Qt::Horizontal, "N°");
    model->setHeaderData(1, Qt::Horizontal, "Qte");
    model->setHeaderData(2, Qt::Horizontal, "Nom");
    model->setHeaderData(3, Qt::Horizontal, "Prix");
    qDebug()<<"is OK?";

    ui->tableView_articles->setModel(model);
    ui->tableView_articles->horizontalHeader()->setFixedHeight(50); // Définit la hauteur à 50 pixels
    ui->tableView_articles->setColumnWidth(0, 65);
    ui->tableView_articles->setColumnWidth(1,65);
    ui->tableView_articles->setColumnWidth(2,739);
    ui->tableView_articles->setColumnWidth(3,170);
    ui->tableView_articles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Permet de créer une connexion avec le dongle NFC
    nfcManager = new NfcManager(this);

    if(nfcManager->isRunning()){
        qDebug() << "Déja en route";
    }
    else{

        if(nfcManager->startDiscovery())
        {
            qDebug() << "Discovery is ok";
            nfcManager->start();
        }
        else
        {
            qDebug() << "Discovery is not ok";
            QMessageBox::warning(this, "Dongle NFC", "Un problème a été detecté avec le dongle NFC");
        }
    }

    connect(nfcManager,&NfcManager::cardDetected,this,&MainWindow::onCardDetected);


}


//Suppression pour libérer l'alocation mémoire

MainWindow::~MainWindow()
{
    delete ui;
    delete sound;
}



//Fonctions crées pour optimisation

void MainWindow::updateRowNumbers() {
    QAbstractItemModel *model = ui->tableView_articles->model();
    for (int i = 0; i < model->rowCount(); ++i) {
        model->setData(model->index(i, 0), QString::number(i + 1)); // Met à jour les numéros
    }
}


void MainWindow::error(bool etat)
{
    caisseBloque=etat;
    //qDebug() << "Appelle de la fonction error";

    if(etat==1){
        ui->label_DerArticle->setStyleSheet("background-color: rgb(255, 144, 17); color: rgb(0, 0, 0);");
        this->setStyleSheet("QWidget { background-color: #2E2E2E; }");
        sound->play();
    }
    else{
        ui->label_DerArticle->setStyleSheet("background-color: white;color: rgb(0, 0, 0);");
        this->setStyleSheet("QWidget { background-color: #c1c1c1; }");
    }

    ui->pushButton_1->setDisabled(etat);
    ui->pushButton_2->setDisabled(etat);
    ui->pushButton_3->setDisabled(etat);
    ui->pushButton_4->setDisabled(etat);
    ui->pushButton_5->setDisabled(etat);
    ui->pushButton_6->setDisabled(etat);
    ui->pushButton_7->setDisabled(etat);
    ui->pushButton_8->setDisabled(etat);
    ui->pushButton_9->setDisabled(etat);
    ui->pushButton_0->setDisabled(etat);
    ui->pushButton_00->setDisabled(etat);
    ui->pushButton_virgule->setDisabled(etat);
    ui->pushButton_quantite->setDisabled(etat);
    ui->pushButton_valider->setDisabled(etat);
    ui->pushButton_supp->setDisabled(etat);
    ui->pushButton_supprDerLigne->setDisabled(etat);
    ui->pushButton_supprLigne->setDisabled(etat);
    ui->pushButton_remise->setDisabled(etat);
    ui->pushButton_payer->setDisabled(etat);
    ui->label_EAN->clear();
}

void MainWindow::removeSpecificLine(int pos)
{
    QAbstractItemModel *model = ui->tableView_articles->model();
    int rowCount = model->rowCount();

    ///Permet de vérifier si le tableau n'est pas vide ou qu'il y a une erreur dans la saisie de "pos"
    if (rowCount == 0 || pos < 0 || pos >= rowCount) {
        qDebug()<<pos;
        ui->label_DerArticle->setText("Aucune ligne à supprimer");
        this->error(1);
    }
    else{
        ///Permet de récuperer la valeur de la 2ème colonne à une ligne spécifique
        QModelIndex productPrice = model->index(pos, 3);
        QString valuePrice = model->data(productPrice).toString();
        //qDebug() << value;

        ///Permet d'enlever le symbole "€" apres le prix
        int enlvEuro = valuePrice.indexOf("€", Qt::CaseInsensitive);
        double valueAsDouble = valuePrice.left(enlvEuro).trimmed().toDouble();

        ///Permet de récuperer l'ancien prix total affiché sans le symbole "€"
        QString oldPrice = ui->label_prix->text();
        int removeEuro = oldPrice.indexOf("€", Qt::CaseInsensitive);
        double valueOldPrice = oldPrice.left(removeEuro).trimmed().toDouble();
        qDebug() << oldPrice;
        qDebug() << removeEuro;
        qDebug() << valueOldPrice;

        ///Permet de mettre à jour la nouvelle valeure du prix totale
        double nvlValeur = valueOldPrice - valueAsDouble;
        qDebug() << nvlValeur;
        ui->label_prix->setText(QString::number(nvlValeur, 'f', 2) + "€");

        model->removeRow(pos);
        updateRowNumbers();
        QModelIndex productName = model->index(ui->tableView_articles->model()->rowCount() - 1, 2);
        QString valueName = model->data(productName).toString();
        ui->label_DerArticle->setText(valueName);
    }
}

void MainWindow::verifierEAN()
{
    QString content = ui->label_EAN->text();

    ///Cherche si il y a un "x" dans label_EAN
    int xIndex = content.indexOf("x", Qt::CaseInsensitive);
    QString valeurAvantX;
    if (xIndex == -1) {
        //qDebug() << "Aucun 'x' trouvé dans l'entrée";
        valeurAvantX = "1";
    }
    else
    {
        valeurAvantX = content.left(xIndex).trimmed();
    }

    /// Récupérer le code EAN après "x"
    QString codeEAN = content.mid(xIndex + 1).trimmed();

    static const QRegularExpression regex("^[0-9]+$");

    // Vérifier que le champ n'est pas vide et contient uniquement des chiffres
    if (codeEAN.isEmpty() || !regex.match(codeEAN).hasMatch()) {
        qDebug() << "EAN invalide ou vide : " << codeEAN;
        ui->label_EAN->clear();
        return;
    }

    // Vérifier si le produit existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT Nom, Prix, StockTotal FROM produit WHERE EAN = :ean");
    query.bindValue(":ean", codeEAN);

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        ui->label_EAN->clear();
        return;
    }

    // Vérifier si on a trouvé un produit
    if (query.next()) {
        ui->label_DerArticle->setStyleSheet("background-color: white;color: rgb(0, 0, 0);");
        QString nom = query.value(0).toString();
        double prix = query.value(1).toDouble();
        QString quantite = valeurAvantX;
        qDebug() << "Produit trouvé : Nom =" << nom << ", Prix =" << prix << "€, Quantité =" << quantite;

        // Affichage dans les widgets
        ui->label_DerArticle->setText(nom);
        //ui->label_prix->setText(QString::number(prix) + "€");

        // Ajouter au tableau si non présent, sinon incrémenter la quantité
        QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->tableView_articles->model());
        if (!model) return;

        QString ancienPrix = ui->label_prix->text();

        int enlvEuro = ancienPrix.indexOf("€", Qt::CaseInsensitive);
        QString valeurAvantEuro = ancienPrix.left(enlvEuro).trimmed();

        double tt = prix * quantite.toDouble();
        double ancienPrixDouble = tt+valeurAvantEuro.toDouble();

        int rowIndex = model->rowCount(); // Récupère le nouvel index de la ligne
        QList<QStandardItem *> newRow;
        newRow.append(new QStandardItem(QString::number(rowIndex + 1))); // Numéro de ligne
        newRow.append(new QStandardItem(quantite)); // Quantité
        newRow.append(new QStandardItem(nom)); // Nom
        newRow.append(new QStandardItem(QString::number(tt, 'f', 2) + "€"));
        model->appendRow(newRow);
        ui->tableView_articles->scrollToBottom();

        ui->label_prix->setText(QString::number(ancienPrixDouble, 'f', 2) + "€");
        // Effacer le champ EAN après ajout
        ui->label_EAN->clear();
        remiseValable=true;
    } else {
        qDebug() << "Produit non trouvé pour EAN :" << codeEAN;
        this->error(1);
        ui->label_DerArticle->setText("Produit non trouvé.");
    }
}


//Paramètrage des touches basique

void MainWindow::on_pushButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString currentText = ui->label_EAN->text();
        ui->label_EAN->setText(currentText + button->text());
        // qDebug() << button->text();
    }
}

//Paramètrage des touches pour effacer

void MainWindow::on_pushButton_supp_clicked()
{
    QString currentText = ui->label_EAN->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1); // Supprime le dernier caractère
        ui->label_EAN->setText(currentText);
    }
}
void MainWindow::on_pushButton_clear_clicked()
{
    if(caisseBloque==true){
        this->error(0);

        QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->tableView_articles->model());
        QModelIndex productName = model->index(ui->tableView_articles->model()->rowCount() - 1, 2);
        QString valueName = model->data(productName).toString();
        ui->label_DerArticle->setText(valueName);
    }
    else{
        ui->label_EAN->clear();
    }
}

void MainWindow::on_pushButton_supprDerLigne_clicked()
{
    ui->label_EAN->clear();
    this->removeSpecificLine(ui->tableView_articles->model()->rowCount() - 1);
    remiseValable=true;
}
void MainWindow::on_pushButton_supprLigne_clicked()
{
    int pos = ui->label_EAN->text().toInt() - 1;
    ui->label_EAN->clear();
    this->removeSpecificLine(pos);
}


//Paramétrage de la docuhette

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // Vérifie si la touche pressée correspond à "Entrée"
    if(caisseBloque==false){
        ui->label_EAN->setFocus();

        if (event->text() == "\n" || event->text() == "\r") {
            // Efface le texte du label
            verifierEAN();
            ui->label_EAN->clear();
            // Appelle la fonction de vérification

        }
        if(event->text() == "\b"){
            QString currentText = ui->label_EAN->text();
            if (!currentText.isEmpty()) {
                currentText.chop(1); // Supprime le dernier caractère
                ui->label_EAN->setText(currentText);
            }
        }
        else {
            // Ajoute le texte de la touche pressée au label
            //qDebug() << event->text();
            QString currentText = ui->label_EAN->text();
            ui->label_EAN->setText(currentText + event->text());
        }
    }
}


//Paramétrage modif prix et paiement

void MainWindow::on_pushButton_remise_clicked()
{
    if(remiseValable==true){
        if(ui->label_EAN->text()==""){
            this->error(1);
            ui->label_DerArticle->setText("Saisir la remise à appliquer");
        }
        else{
            QAbstractItemModel *model = ui->tableView_articles->model();

            if (model->rowCount() > 0) {
                //unsigned int remise = ui->label_EAN->text().toDouble();
                if(ui->label_EAN->text().toDouble()<=100 && ui->label_EAN->text().toDouble()>=1){
                    // Récupérer l'index de la dernière ligne
                    int lastRow = model->rowCount() - 1;
                    double remise = ui->label_EAN->text().toDouble();

                    // Récupérer l'index de la 4ème colonne (index 3)
                    QModelIndex index = model->index(lastRow, 3);

                    // Récupérer la valeur de la 3ème colonne (sous forme de QString)
                    QString value = model->data(index).toString();

                    int enlvEuro = value.indexOf("€", Qt::CaseInsensitive);
                    QString valeurAvantEuro = value.left(enlvEuro).trimmed();
                    double valueAsDouble = valeurAvantEuro.toDouble();
                    double reduction = valueAsDouble * (1-(remise/100));

                    QString ancienPrix = ui->label_prix->text();

                    int enlvEuroAncienPrix = ancienPrix.indexOf("€", Qt::CaseInsensitive);
                    QString valeurAvantEuroAncienPrix = ancienPrix.left(enlvEuroAncienPrix).trimmed();
                    double valeurAvantEuroAncienPrixAsDouble = valeurAvantEuroAncienPrix.toDouble();

                    double nvlValeur = valeurAvantEuroAncienPrixAsDouble - (valueAsDouble-reduction);
                    //qDebug() <<nvlValeur;
                    model->setData(index, QString::number(reduction, 'f', 2) + "€" + "-" + QString::number(remise) + "%");

                    ui->label_prix->setText(QString::number(nvlValeur, 'f', 2) + "€");
                    ui->label_EAN->clear();
                    remiseValable=false;
                }
                else{
                    this->error(1);
                    ui->label_DerArticle->setText("Remise incorecte");
                }

            }
            else{
                //Fonction error qui emet un son puis bloque l'acces aux touches
                this->error(1);
                //ui->label_DerArticle->setPlainText("Aucun article dans la liste");
                ui->label_DerArticle->setText("Aucun article dans la liste");
            }
        }
    }
    else{
        this->error(1);
        ui->label_DerArticle->setText("Remise déja effectué sur le produit");
    }

}
void MainWindow::on_pushButton_valider_clicked()
{
    this->verifierEAN();
}

// Permet de détécter la carte quand elle est passé sur le dongle NFC

void MainWindow::onCardDetected(const std::vector<uint8_t> &cardID)
{
    //Arrêter la découverte NFC proprement
    nfcManager->stopDiscovery();

    qDebug() << "Emit CardId : " << cardID;

    if (!cardID.empty()) {
        QString cardIDStr;
        for (uint8_t byte : cardID) {
            cardIDStr.append(QString::number(byte, 16).toUpper() + " ");
        }
        cardIDStr = cardIDStr.trimmed(); // Supprime l'espace en trop à la fin

        qDebug() << "Card ID: " << cardIDStr;

        // Requête pour récupérer les informations de l'utilisateur
        QSqlQuery info_user;
        info_user.prepare("SELECT Nom, Prenom, solde FROM client WHERE Id_Client = :Id_Client");
        info_user.bindValue(":Id_Client", cardIDStr);

        if (info_user.exec()) {
            if (info_user.next()) {
                QString nom = info_user.value(0).toString();
                QString prenom = info_user.value(1).toString();
                double solde = info_user.value(2).toDouble();

                QString result =  " Nom: " + nom + "\n Prénom: " + prenom + "\n Solde: " + QString::number(solde, 'f', 2) + "€";

                ui->label_carte->setText(result);
            } else {
                ui->label_carte->setText("Carte inconnue.");
            }
        } else {
            qDebug() << "Erreur SQL: " << info_user.lastError().text();
            ui->label_carte->setText("Erreur lors de la recherche.");
        }
    }


    // redémarrer la découverte NFC proprement
    nfcManager->startDiscovery();
    //nfcManager->start();
}

// Permet de sortir un ticket et débiter la carte du client

void MainWindow::on_pushButton_payer_clicked()
{
    //GENERATION D'UN FICHIER TXT
    // Nom du fichier
    QString currentDateTime = QDateTime::currentDateTime().toString("dd-MM-yyyy_HH-mm-ss");

    QString fileName = QDir::currentPath() + "/ticket"+currentDateTime+".txt";

    qDebug() << "Répertoire courant :" << QDir::currentPath();



    // Création et ouverture du fichier en mode écriture
    QFile file(fileName);


    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QAbstractItemModel *model = ui->tableView_articles->model();
        int rowCount = model->rowCount();
        qDebug() << "Fichier ouvert avec succès";
        QTextStream out(&file);
        out << "------------------------------------------\n"
               "            Cafeteria Pompier\n"
               " 28 Rue du Maréchal de Lattre de Tassigny,\n"
               "            45700 Villemandeur\n"
               "            Tél: 02 38 90 07 37\n"
               "------------------------------------------\n" << endl;
        out << "Date et heure : " << currentDateTime << endl;
        out << "------------------------------------------\n"
               "Qte  Désignation                 Prix (€) \n"
               "------------------------------------------\n";

        for (int pos = 0; pos < rowCount; pos++) {
            QModelIndex productQte = model->index(pos, 1);
            QModelIndex productName = model->index(pos, 2);
            QModelIndex productPrix = model->index(pos, 3);

            QString valueQte = model->data(productQte).toString();
            unsigned int valueQteDebite = model->data(productQte).toInt();
            QString valueName = model->data(productName).toString();
            QString valuePrix = model->data(productPrix).toString();

            QSqlQuery Qte_avant;
            Qte_avant.prepare("SELECT StockTotal FROM produit WHERE Nom = :nom");
            Qte_avant.bindValue(":nom", valueName);

            if (!Qte_avant.exec()) {
                qDebug() << "Erreur lors de l'exécution de la requête SELECT:" << Qte_avant.lastError().text();
                return;
            }

            if (!Qte_avant.next()) {
                qDebug() << "Erreur: Produit non trouvé dans la base de données.";
                return;
            }

            // Calcul de la nouvelle quantité en stock
            unsigned int QteAp = Qte_avant.value(0).toUInt() - valueQteDebite;
            qDebug() << "Nouvelle quantité après débit: " << QteAp;


            // Mise à jour du stock dans la base de données
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE produit SET StockTotal = :qte WHERE Nom = :nom");
            updateQuery.bindValue(":qte", QteAp);
            updateQuery.bindValue(":nom", valueName);

            if (!updateQuery.exec()) {
                qDebug() << "Erreur lors de la mise à jour du stock:" << updateQuery.lastError().text();
            } else {
                qDebug() << "Mise à jour réussie. Nouvelle quantité: " << QteAp;


            // Ajustement des longueurs pour l'affichage correct
            valueQte = valueQte.leftJustified(5, ' ');         // Quantité sur 5 caractères
            valueName = valueName.left(25).leftJustified(25, ' '); // Nom tronqué à 20 caractères et justifié
            valuePrix = valuePrix.rightJustified(8, ' ');      // Prix aligné à droite sur 8 caractères

            out << valueQte << valueName << valuePrix << endl;
            }}
        out << "------------------------------------------\n"
               "Total: " << ui->label_prix->text() << endl;
        QString clientId = ui->label_carte->text();
        out << "------------------------------------------\n"
               "Nom sur la carte: " << ui->label_carte->text() << endl;

        // Récupération du solde actuel
        QSqlQuery solde_actuel;
        solde_actuel.prepare("SELECT solde FROM client WHERE Id_Client = :Id_Client");
        solde_actuel.bindValue(":Id_Client", clientId);


        out << "Montant payé: " << ui->label_prix->text()<< endl;
        out << "------------------------------------------\n"
               "Merci de votre visite                     \n"
               "------------------------------------------\n";
        file.close();
        qDebug() << "Fichier écrit avec succès :" << fileName;
    } else {
        qDebug() << "Erreur lors de l'ouverture du fichier !";
    }
}

// Permet de revenir au menu

void MainWindow::on_pushButton_home_clicked()
{

    disconnect(nfcManager,&NfcManager::cardDetected,this,&MainWindow::onCardDetected);

    if (nfcManager) {
        qDebug() << "Demande Arrêt du thread NFC2...";
        nfcManager->stopRun(); // Ferme le gestionnaire NFC proprement
        qDebug() << "Arrêt du thread NFC2 demandé ...";
        qDebug() << nfcManager;
        delete nfcManager;
        nfcManager = nullptr; // Évite tout accès à un pointeur dangling
    }

    qDebug() << "Arrêt du thread NFC2...";
    db.close();

    Menu *menu = new Menu();
    menu->setWindowIcon(QIcon(QDir::toNativeSeparators("C:/Users/tristan/Documents/QTcreator/Projet_pompier2/images/flamme.png")));
    menu->setWindowTitle("Menu");
    menu->show();
    QThread::msleep(100);
    this->close();
}

