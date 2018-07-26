#include "studentdb.h"
#include "ui_studentdb.h"
#include <QDir>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>


StudentDB::StudentDB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentDB)
{
    ui->setupUi(this);
    QString path ;
        path="/home/rpi/Desktop/StudentDatabase";
        QDir file;
        //QString filepath=QDir::path();
        QString filename = file.path() + QDir::separator() + "student.db";

        if(!createDB(filename))
        {
            QMessageBox::critical(this,
                                  tr("Database not found"),
                                  tr("Database not found. The application will be closed."),
                                  QMessageBox::Ok);
            qApp->exit();
        }

}

StudentDB::~StudentDB()
{
    delete ui;
}

void StudentDB::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
bool StudentDB::createDB(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbname);

        if(db.open())
        {

            bool found = false;
            foreach (QString table, db.tables())
            {
                if(table == "student")
                {
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                QSqlQuery query(db);
                query.exec("CREATE TABLE student (name VARCHAR(32), Roll_No VARCHAR(16))");
            }

            model = new QSqlTableModel(this,db);
            model->setTable("student");

            model->setEditStrategy(QSqlTableModel::OnFieldChange);
            model->select();


        }
        else
            return false;

        return true;



}

void StudentDB::on_pushButtonAdd_clicked()
{
    QString Name=ui->textName->toPlainText();
        QString RollNo=ui->textRollNo->toPlainText();

        AddNewStudent(Name,RollNo);
}
void StudentDB::AddNewStudent(QString Name, QString Roll_No)
{
    QSqlRecord rec = model->record();
        rec.setValue("name",Name);
        rec.setValue("Roll_No",Roll_No);


        // insert a new record (-1)
        model->insertRecord(-1,rec);
        ui->textName->setText("");
        ui->textRollNo->setText("");

}

void StudentDB::on_pushButtonDelete_clicked()
{
    QModelIndex sample = ui->treeView->currentIndex();
        if( sample.row() >= 0 )
        {
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this, tr("Remove Student"),
                                        QString(tr("Remove Student ?")),
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                model->removeRow(sample.row());
            }
        }
}

void StudentDB::on_pushButtonView_clicked()
{
    QTreeView  *view;
        view=ui->treeView;


         ViewDetails();

}
void StudentDB::ViewDetails()
{
    QTreeView *view=ui->treeView;
       view->setModel(model);

}
