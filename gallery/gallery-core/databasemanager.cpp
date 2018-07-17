#include "databasemanager.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path) :
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))), //database driver is selected
    albumDao(*mDatabase), //initialized with the mDatabase dereferenced pointer
    pictureDao(*mDatabase)
{
    mDatabase->setDatabaseName(path); //configuring the database name
    mDatabase->open(); //opening the connection

    albumDao.init();
    pictureDao.init();
}

void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError)
    {
        qDebug() << "Query OK:"  << query.lastQuery();
    } else
    {
       qWarning() << "Query NO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close(); //connection is closed
    delete mDatabase; //pointer is properly deleted
}
