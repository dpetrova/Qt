#include "picturedao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "Picture.h"
#include "DatabaseManager.h"

using namespace std;

PictureDao::PictureDao(QSqlDatabase& database) :
    mDatabase(database)
{
}

void PictureDao::init() const
{
    if (!mDatabase.tables().contains("pictures")) {
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE pictures")
        + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
        + "album_id INTEGER, " //foreign key is expressed in the album_id INTEGER syntax
        + "url TEXT)");
        DatabaseManager::debugQuery(query);
    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture& picture) const
{
    QSqlQuery query(mDatabase);
    query.prepare(QString("INSERT INTO pictures")
        + " (album_id, url)"
        + " VALUES ("
        + ":album_id, "
        + ":url"
        + ")");
    query.bindValue(":album_id", albumId);
    query.bindValue(":url", picture.getFileUrl());
    query.exec();
    DatabaseManager::debugQuery(query);
    picture.setId(query.lastInsertId().toInt());
    picture.setAlbumId(albumId);
}

void PictureDao::removePicture(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
}

void PictureDao::removePicturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();
    DatabaseManager::debugQuery(query);
}

QVector<Picture*> PictureDao::picturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();
    DatabaseManager::debugQuery(query);
    QVector<Picture*> list;
    while(query.next())
    {
        Picture* picture = new Picture();
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("album_id").toInt());
        picture->setFileUrl(query.value("url").toString());
        list.append(picture);
    }
    return list;
}
