#ifndef PICTUREIMAGEPROVIDER_H
#define PICTUREIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QCache>

class PictureModel;

//handle image asynchronos loading
class PictureImageProvider : public QQuickImageProvider
{
public:

    static const QSize THUMBNAIL_SIZE;

    PictureImageProvider(PictureModel* pictureModel);

    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override; //load pixmap

    QPixmap* pictureFromCache(const QString& filepath, const QString& pictureSize);

private:
    PictureModel* mPictureModel; //to be able to retrieve fileUrl
    QCache<QString, QPixmap> mPicturesCache;
};
#endif // PICTUREIMAGEPROVIDER_H
