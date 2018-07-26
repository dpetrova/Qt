#ifndef STUDENTDB_H
#define STUDENTDB_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
    class StudentDB;
}

class StudentDB : public QMainWindow {
    Q_OBJECT
public:
    StudentDB(QWidget *parent = 0);
    ~StudentDB();
    QSqlTableModel *model;
        QSqlDatabase db;
         bool createDB(QString dbname);
         void setName(const QString n);
         void setRollNO(const QString p);
         void AddNewStudent(QString Name,QString Roll_No);
         void ViewDetails();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::StudentDB *ui;

private slots:
    void on_pushButtonView_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonAdd_clicked();
};

#endif // STUDENTDB_H
