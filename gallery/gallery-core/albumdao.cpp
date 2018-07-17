#include "albumdao.h"
#include "DatabaseManager.h"
#include "Album.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant> //QSqlQuery::bind() expects a QVariant as a parameter value

using namespace std;

AlbumDao::AlbumDao(QSqlDatabase& database) :
    mDatabase(database) //the mDatabase field is initialized with the database parameter
{
}

void AlbumDao::init() const
{
    if (!mDatabase.tables().contains("albums")) //if the table albums class does not exist
    {
        //QSqlQuery query is created that will use the mDatabase connection to be executed
        QSqlQuery query(mDatabase);

        //executing a query as simply pass the QString type of your query
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");

        DatabaseManager::debugQuery(query);
    }
}

//add album
void AlbumDao::addAlbum(Album& album) const
{
    QSqlQuery query(mDatabase);

    //function which contains placeholders for parameters provided later (name)
    query.prepare("INSERT INTO albums (name) VALUES (:name)");

    //bind :name to the value of the album.getName()
    query.bindValue(":name", album.getName());

    //when the query.exec() function is executed, the bound values are properly replaced
    query.exec();

    //retrieve information about the query with the query.lastInsertId() function,
    //which returns a QVariant value containing the ID of the album row we just inserted
    album.setId(query.lastInsertId().toInt());

    DatabaseManager::debugQuery(query);
}

//update album
void AlbumDao::updateAlbum(const Album& album)const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE albums SET name = (:name) WHERE id = (:id)");
    query.bindValue(":name", album.getName());
    query.bindValue(":id", album.getId());
    query.exec();
    DatabaseManager::debugQuery(query);
}

//remove album
void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM albums WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
}

//get all albums in the database
QVector<Album*> AlbumDao::albums() const
{
    QSqlQuery query("SELECT * FROM albums", mDatabase);
    query.exec();
    QVector<Album*> list;
    while(query.next()) //walk through multiple rows for a given request
    {
        Album* album = new Album();
        //takes a column name parameter and returns a QVariant value that is casted to the proper type
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list.append(album);
    }
    return list;
}
