#ifndef ALBUM_H
#define ALBUM_H

#include "gallery-core_global.h"

#include <QString>

//the symbols you want to mark as public, you just have to use the GALLERYCORESHARED_EXPORT macro
class GALLERYCORESHARED_EXPORT Album
{

public:
    explicit Album(const QString& name = "");
    int getId() const;
    void setId(int id);
    QString getName() const;
    void setName(const QString& name);

private:
    int mId;
    QString mName;
};

#endif // ALBUM_H
