#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStringList>
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class connexion;
}
QT_END_NAMESPACE
class connexion : public QMainWindow {
    Q_OBJECT

public:
    explicit connexion(QWidget *parent = nullptr);
    ~connexion();
    Ui::connexion *ui;

private slots:
    void on_pushButton_val_clicked();
    void on_checkBox_print_stateChanged(int arg1);
    void keyPressEvent(QKeyEvent *event);

protected :
    void closeEvent(QCloseEvent* event);

private:

    Menu* menu;
    QSqlDatabase db;
    QStringList usernames;
    QStringList passwords;
    QStringList droits;
    QString usr;
    QString pwd;
    unsigned short int compteur=0;
};

#endif // CONNEXION_H
