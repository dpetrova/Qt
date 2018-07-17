#include "album.h"

Album::Album(const QString& name) :
    mId(-1), //by default, an invalid id
    mName(name)
{
}

int Album::getId() const
{
    return mId;
}

void Album::setId(int id)
{
    mId = id;
}

QString Album::getName() const
{
    return mName;
}

void Album::setName(const QString& name)
{
    mName = name;
}
