#ifndef MENUSTOCK_H
#define MENUSTOCK_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStringList>
#include <QDir>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>
#include "addstock.h"
#include "delstock.h"
#include "modstock.h"

namespace Ui {
class MenuStock;
}

class MenuStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuStock(QWidget *parent = nullptr);
    ~MenuStock();

private slots:

    void on_commandLinkButton_add_clicked();

    void on_pushButton_back_clicked();

    void on_commandLinkButton_del_clicked();

    void on_commandLinkButton_change_clicked();

private:
    Ui::MenuStock *ui;
    AddStock* addStock;
    DelStock* delStock;
    ModStock* modStock;
};

#endif // MENUSTOCK_H
