#include "createemployee.h"
#include "ui_createemployee.h"

#include <QMessageBox>

CreateEmployee::CreateEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateEmployee)
{
    ui->setupUi(this);

    Login dbConn; //to get db connection
    if(!dbConn.dbConnectionOpen()){
        ui->label_sec_status->setText("Failed to open the database");
    }
    else{
        ui->label_sec_status->setText("Connected...");
    }
}

CreateEmployee::~CreateEmployee()
{
    delete ui;
}

void CreateEmployee::on_saveButton_clicked()
{
    Login dbConn;
    QString username, name, surname, age, password;
    username = ui->lineEdit_username->text();
    name = ui->lineEdit_name->text();
    surname = ui->lineEdit_surname->text();
    age = ui->lineEdit_age->text();
    password = ui->lineEdit_password->text();

    if(!dbConn.dbConnectionOpen()){ //open the connection
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query;
    query.prepare("insert into employeeinfo (username, name, surname, age, password) values ('"+username+"', '"+name+"', '"+surname+"', '"+age+"', '"+password+"')");

    if(query.exec())
    {
        QMessageBox::information(this, tr("Save"), tr("Saved"));
        dbConn.dbConnectionClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}

void CreateEmployee::on_updateButton_clicked()
{
    Login dbConn;
    QString username, name, surname, age, password;
    username = ui->lineEdit_username->text();
    name = ui->lineEdit_name->text();
    surname = ui->lineEdit_surname->text();
    age = ui->lineEdit_age->text();
    password = ui->lineEdit_password->text();

    if(!dbConn.dbConnectionOpen()){ //open the connection
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query;
    //TODO: should select certain person and get id (here update the person with id=4)
    query.prepare("update employeeinfo set username='"+username+"', name='"+name+"', surname='"+surname+"', age='"+age+"', password='"+password+"' where id=4");

    if(query.exec())
    {
        QMessageBox::information(this, tr("Update"), tr("Updated"));
        dbConn.dbConnectionClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}

void CreateEmployee::on_deleteButton_clicked()
{
    Login dbConn;
    QString username;
    username = ui->lineEdit_username->text();

    if(!dbConn.dbConnectionOpen()){ //open the connection
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query;
    //TODO: should select certain person and delete it
    query.prepare("delete from employeeinfo where username='"+username+"'");

    if(query.exec())
    {
        QMessageBox::information(this, tr("Delete"), tr("Deleted"));
        dbConn.dbConnectionClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}

void CreateEmployee::on_loadTableButton_clicked()
{
    Login dbConn;
    QSqlQueryModel *model = new QSqlQueryModel();

    dbConn.dbConnectionOpen(); //open db connection

    QSqlQuery *query =  new QSqlQuery(dbConn.mydb);
    //query->prepare("select * from employeeinfo");
    query->prepare("select name, surname, age from employeeinfo");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);

    dbConn.dbConnectionClose(); //close db connection

    qDebug() << model->rowCount();
}

void CreateEmployee::on_loadListButton_clicked()
{
    Login dbConn;
    QSqlQueryModel *model = new QSqlQueryModel();

    dbConn.dbConnectionOpen(); //open db connection

    QSqlQuery *query =  new QSqlQuery(dbConn.mydb);
    query->prepare("select name from employeeinfo");
    query->exec();
    model->setQuery(*query);
    ui->listView->setModel(model);

    dbConn.dbConnectionClose(); //close db connection

    qDebug() << model->rowCount();
}


void CreateEmployee::on_loadComboboxButton_clicked()
{
    Login dbConn;
    QSqlQueryModel *model = new QSqlQueryModel();

    dbConn.dbConnectionOpen(); //open db connection

    QSqlQuery *query =  new QSqlQuery(dbConn.mydb);
    query->prepare("select name from employeeinfo");
    query->exec();
    model->setQuery(*query);
    ui->comboBox->setModel(model);

    dbConn.dbConnectionClose(); //close db connection

    qDebug() << model->rowCount();
}

//load selected person from combobox into create/update form
void CreateEmployee::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString name = ui->comboBox->currentText(); //get text of combo box selected item

    Login dbConn;

    if(!dbConn.dbConnectionOpen()){ //open the connection
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query;
    query.prepare("select * from employeeinfo where name='"+name+"'");

    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_username->setText(query.value(4).toString()); //4 is the column index in the db table
            ui->lineEdit_name->setText(query.value(1).toString());
            ui->lineEdit_surname->setText(query.value(2).toString());
            ui->lineEdit_age->setText(query.value(3).toString());
            ui->lineEdit_password->setText(query.value(5).toString());
        }
        dbConn.dbConnectionClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}

//load selected person from table view into create/update form
void CreateEmployee::on_tableView_clicked(const QModelIndex &index) //single click
{
    QString val = ui->tableView->model()->data(index).toString(); //take the value in the index of selected cell in table view
    qDebug() << val;

    Login dbConn;
    if(!dbConn.dbConnectionOpen()){ //open the connection
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query;
    query.prepare("select * from employeeinfo where name='"+val+"' or surname='"+val+"' or age='"+val+"'");

    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_username->setText(query.value(4).toString()); //4 is the column index of username column in the db table
            ui->lineEdit_name->setText(query.value(1).toString());
            ui->lineEdit_surname->setText(query.value(2).toString());
            ui->lineEdit_age->setText(query.value(3).toString());
            ui->lineEdit_password->setText(query.value(5).toString());
        }
        dbConn.dbConnectionClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}

void CreateEmployee::on_tableView_activated(const QModelIndex &index) //double click
{
}

void CreateEmployee::on_listView_clicked(const QModelIndex &index)
{
    QString val = ui->listView->model()->data(index).toString(); //take the value in the index of selected cell in table view
    qDebug() << val;

    Login dbConn;
    if(!dbConn.dbConnectionOpen()){ //open the connection
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query;
    query.prepare("select * from employeeinfo where name='"+val+"'");

    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_username->setText(query.value(4).toString()); //4 is the column index of username column in the db table
            ui->lineEdit_name->setText(query.value(1).toString());
            ui->lineEdit_surname->setText(query.value(2).toString());
            ui->lineEdit_age->setText(query.value(3).toString());
            ui->lineEdit_password->setText(query.value(5).toString());
        }
        dbConn.dbConnectionClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}
