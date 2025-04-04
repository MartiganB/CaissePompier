#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QDir>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QSoundEffect>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QCoreApplication>
#include "nfcmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateRowNumbers();
    void error(bool etat);
    void removeSpecificLine(int pos);
    void verifierEAN();
    void on_pushButton_clear_clicked();
    void on_pushButton_valider_clicked();
    void on_pushButton_supp_clicked();
    void on_pushButton_supprDerLigne_clicked();
    void on_pushButton_supprLigne_clicked();
    void on_pushButton_remise_clicked();
    void on_pushButton_payer_clicked();
    void on_pushButton_clicked();

    // NFC reader slot
    void onCardDetected(const std::vector<uint8_t> &cardID);


    void on_pushButton_home_clicked();

private:
    void keyPressEvent(QKeyEvent* event) override;
    void disableNumberButtons(bool disable); // Ajoutez cette ligne
    bool remiseValable=false;
    bool caisseBloque=false;

    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSoundEffect *sound;
    NfcManager* nfcManager = nullptr;

};
#endif // MAINWINDOW_H
