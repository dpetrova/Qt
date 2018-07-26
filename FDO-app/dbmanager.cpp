#include "dbmanager.h"

#include <QSqlDatabase>
#include <QDebug>

DbManager& DbManager::instance()
{
    static DbManager singleton;
    return singleton;
}

DbManager::DbManager(const QString& path) :
    db(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))) //database driver is selected
{
    db->setDatabaseName(path); //configuring the database name

    //opening the connection
    if(!db->open())
    {
         qDebug() << "Failed to open the database";
    }
    else{
        qDebug() << "Connected to database";
    }

   //TODO: seed default for users, students, ship, heli,...
}

DbManager::~DbManager()
{
    db->close(); //connection is closed
    db->removeDatabase(QSqlDatabase::defaultConnection); //remove the connection
    //delete db;
}
