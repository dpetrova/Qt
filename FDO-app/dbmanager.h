#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>

class QSqlDatabase; //forward-declared

const QString DATABASE_FILENAME = "fdo.db";

class DbManager
{

public:
    static DbManager& instance(); //singleton
    ~DbManager();

protected:
    DbManager(const QString& path = DATABASE_FILENAME);

private:
    QSqlDatabase* db;

};

#endif // DBMANAGER_H
