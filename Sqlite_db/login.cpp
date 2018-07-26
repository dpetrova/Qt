#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //open db connection
    if(!dbConnectionOpen()){
        ui->label->setText("Failed to open the database");
    }
    else{
        ui->label->setText("Connected...");
    }

    //set username and password icons before fields
    QPixmap usernamePixmap("C:/Users/Dani/Pictures/fdo-admin-icons/username.png");
    usernamePixmap = usernamePixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->label_usernameIcon->setPixmap(usernamePixmap);

    QPixmap passwordPixmap("C:/Users/Dani/Pictures/fdo-admin-icons/pass.png");
    passwordPixmap = passwordPixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->label_passwordIcon->setPixmap(passwordPixmap);
}

Login::~Login()
{
    delete ui;
}

void Login::dbConnectionClose()
{
    mydb.close(); //close database
    mydb.removeDatabase(QSqlDatabase::defaultConnection); //remove the connection
}

bool Login::dbConnectionOpen()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("database1.db");

    if(!mydb.open()){
         qDebug() << "Failed to open the database";
         return false;
    }
    else{
        qDebug() << "Connected to database";
        return true;
    }

}

void Login::on_pushButton_clicked()
{
    QString username, password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();

    if(!dbConnectionOpen()){
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query;
    query.prepare("select * from employeeinfo where username = '"+username+"' and password='"+password+"'");

    if(query.exec())
    {
        int count = 0;
        while(query.next())
        {
            count++;
        }

        if(count == 1){
            ui->label->setText("Username and password are correct");

            dbConnectionClose(); //close db connection

            //close login page and open employeeInfo page
            this->hide();
            CreateEmployee createEmployeePage;
            createEmployeePage.setModal(true);
            createEmployeePage.exec();
        }
        if(count > 1){
            ui->label->setText("Duplicate username and password");
        }
        if(count < 1){
            ui->label->setText("Username and password are not correct");
        }
    }
}
