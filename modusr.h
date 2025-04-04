#ifndef MODUSR_H
#define MODUSR_H

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
class ModUsr;
}

class ModUsr : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModUsr(QWidget *parent = nullptr);
    ~ModUsr();

private slots:
    void on_pushButton_back_clicked();

    void handleComboBoxIndexChanged();

private:
    Ui::ModUsr *ui;
    QSqlDatabase db;
    QStandardItemModel *model;
    QComboBox *comboBox_droit;
};

#endif // MODUSR_H
