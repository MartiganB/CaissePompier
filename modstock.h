#ifndef MODSTOCK_H
#define MODSTOCK_H

#include <QComboBox>
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


namespace Ui {
class ModStock;
}

class ModStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModStock(QWidget *parent = nullptr);
    ~ModStock();

private:

    void on_pushButton_back_clicked();

    Ui::ModStock *ui;
    QSqlDatabase db;
    QStandardItemModel *model;
    QComboBox *comboBox_droit;
};

#endif // MODSTOCK_H
