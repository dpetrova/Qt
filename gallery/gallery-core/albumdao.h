#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <memory>
#include <vector>
#include <QVector>

class QSqlDatabase;
class Album;

class AlbumDao
{
public:
    AlbumDao(QSqlDatabase& database); //QSqlDatabase& parameter is the database connection that will be used for all the SQL queries done by the AlbumDao class
    void init() const; //aims to create the albums table and should be called when mDatabase is opened
    void addAlbum(Album& album) const;
    void updateAlbum(const Album& album) const;
    void removeAlbum(int id) const;
    QVector<Album*> albums() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // ALBUMDAO_H
