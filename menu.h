#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStringList>
#include "gestionmenu.h"
#include "menustock.h"
#include "mainwindow.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    Ui::Menu *ui;

private slots:
    void on_pushButton_deco_clicked();

    void on_commandLinkButton_admin_clicked();

    void on_commandLinkButton_caisse_clicked();

    void on_commandLinkButton_stock_clicked();

protected :
    void closeEvent(QCloseEvent* event);

private:
    QSqlDatabase db;
    GestionMenu *gestMenu;
    MenuStock* menuStock;
    MainWindow* caisse;

};

#endif // MENU_H
