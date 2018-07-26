#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "createemployee.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void dbConnectionClose();
    bool dbConnectionOpen();
    QSqlDatabase mydb;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;    
};

#endif // LOGIN_H
