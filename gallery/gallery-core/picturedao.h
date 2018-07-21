#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <memory>
#include <vector>
#include <QVector>

class QSqlDatabase;
class Picture;

using namespace std;

class PictureDao
{
public:
    explicit PictureDao(QSqlDatabase& database);
    void init() const;
    void addPictureInAlbum(int albumId, Picture& picture) const;
    void removePicture(int id) const;
    void removePicturesForAlbum(int albumId) const;
    //QVector<Picture*> picturesForAlbum(int albumId) const;
    unique_ptr<vector<unique_ptr<Picture>>> picturesForAlbum(int albumId) const;

private:
    QSqlDatabase& mDatabase;
};


#endif // PICTUREDAO_H
