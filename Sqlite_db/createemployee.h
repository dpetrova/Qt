#ifndef CREATEEMPLOYEE_H
#define CREATEEMPLOYEE_H

#include "login.h"

#include <QDialog>

namespace Ui {
class CreateEmployee;
}

class CreateEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit CreateEmployee(QWidget *parent = 0);
    ~CreateEmployee();

private slots:
    void on_saveButton_clicked();

    void on_updateButton_clicked();

    void on_deleteButton_clicked();

    void on_loadTableButton_clicked();

    void on_loadListButton_clicked();

    void on_loadComboboxButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::CreateEmployee *ui;
};

#endif // CREATEEMPLOYEE_H
