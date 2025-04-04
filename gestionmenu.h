#ifndef GESTIONMENU_H
#define GESTIONMENU_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStringList>
#include "addusr.h"
#include "delusr.h"
#include "modusr.h"

namespace Ui {
class GestionMenu;
}

class GestionMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionMenu(QWidget *parent = nullptr);
    ~GestionMenu();

private slots:

    void on_commandLinkButton_add_clicked();

    void on_pushButton_back_clicked();

    void on_commandLinkButton_del_clicked();

    void on_commandLinkButton_change_clicked();

protected :
    void closeEvent(QCloseEvent* event);

private:
    Ui::GestionMenu *ui;
    AddUsr* addUsr;
    DelUsr* delUsr;
    ModUsr* modUsr;
};

#endif // GESTIONMENU_H
