#ifndef DELSTOCK_H
#define DELSTOCK_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QtSql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDir>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>
#include <QCheckBox>

namespace Ui {
class DelStock;
}

class DelStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit DelStock(QWidget *parent = nullptr);
    ~DelStock();

private:
    Ui::DelStock *ui;
    QSqlDatabase db;
    QStandardItemModel *model;
    QCheckBox *checkBox;
};

#endif // DELSTOCK_H
