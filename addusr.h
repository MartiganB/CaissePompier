#ifndef ADDUSR_H
#define ADDUSR_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class AddUsr;
}

class AddUsr : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddUsr(QWidget *parent = nullptr);
    ~AddUsr();

private slots:
    void on_pushButton_val_clicked();

    void on_pushButton_back_clicked();

    void on_checkBox_print_stateChanged(int arg1);

private:
    Ui::AddUsr *ui;
    QSqlDatabase db;
};

#endif // ADDUSR_H
