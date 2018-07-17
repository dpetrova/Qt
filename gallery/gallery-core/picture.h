#ifndef PICTURE_H
#define PICTURE_H

#include <QUrl>
#include <QString>

#include "gallery-core_global.h"

class GALLERYCORESHARED_EXPORT Picture //add the GALLERYCORESHARED_EXPORT macro to export the class from the library
{
public:
    Picture(const QString& filePath = "");
    Picture(const QUrl& fileUrl);

    int getId() const;
    void setId(int id);

    int getAlbumId() const;
    void setAlbumId(int albumId);

    QUrl getFileUrl() const;
    void setFileUrl(const QUrl& fileUrl);
private:
    int mId;
    int mAlbumId;
    QUrl mFileUrl;
};

#endif // PICTURE_H
