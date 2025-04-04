#ifndef ADDSTOCK_H
#define ADDSTOCK_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlError>
namespace Ui {
class AddStock;
}

class AddStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddStock(QWidget *parent = nullptr);
    ~AddStock();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::AddStock *ui;
    QSqlDatabase db;
};

#endif // ADDSTOCK_H
