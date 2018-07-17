#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "AlbumDao.h"
#include "PictureDao.h"

#include <QString>

class QSqlDatabase; //forward-declared
class QSqlQuery;

const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance(); //singleton
    static void debugQuery(const QSqlQuery& query);
    ~DatabaseManager();

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    QSqlDatabase* mDatabase;

public:
    const AlbumDao albumDao;
    const PictureDao pictureDao;
};

#endif // DATABASEMANAGER_H
