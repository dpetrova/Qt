#include "picture.h"

//In first constructor, the static function, QUrl::fromLocalFile, is called
//to provide a QUrl object to the other constructor, which takes a QUrl parameter
Picture::Picture(const QString& filePath) :
    Picture(QUrl::fromLocalFile(filePath))
{
}

Picture::Picture(const QUrl& fileUrl) :
    mId(-1),
    mAlbumId(-1),
    mFileUrl(fileUrl)
{
}

QUrl Picture::getFileUrl() const
{
    return mFileUrl;
}

void Picture::setFileUrl(const QUrl& fileUrl)
{
    mFileUrl = fileUrl;
}

int Picture::getId() const
{
    return mId;
}

void Picture::setId(int id)
{
    mId = id;
}

int Picture::getAlbumId() const
{
    return mAlbumId;
}

void Picture::setAlbumId(int albumId)
{
    mAlbumId = albumId;
}
