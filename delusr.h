#ifndef DELUSR_H
#define DELUSR_H

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
class DelUsr;
}

class DelUsr : public QMainWindow
{
    Q_OBJECT

public:
    explicit DelUsr(QWidget *parent = nullptr);
    ~DelUsr();

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_del_clicked();

private:
    Ui::DelUsr *ui;
    QSqlDatabase db;
    QStandardItemModel *model;
    QCheckBox *checkBox;
};

#endif // DELUSR_H
