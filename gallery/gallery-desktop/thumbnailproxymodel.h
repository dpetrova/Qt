#ifndef THUMBNAILPROXYMODEL_H
#define THUMBNAILPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QHash>
#include <QPixmap>

class PictureModel;

//QIdentityProxyModel, and more generally QAbstractProxyModel,
//are valuable tools to add behavior to an existing model without breaking it
class ThumbnailProxyModel : public QIdentityProxyModel
{
public:
    ThumbnailProxyModel(QObject* parent = 0);

    QVariant data(const QModelIndex& index, int role) const override; //provide the thumbnail data to the client of ThumbnailProxyModel
    void setSourceModel(QAbstractItemModel* sourceModel) override; //register to signals emitted by sourceModel
    PictureModel* pictureModel() const; //helper function that casts the sourceModel to a PictureModel*

private:
    void reloadThumbnails(); //helper function that clears the stored thumbnails before calling generateThumbnails()
    void generateThumbnails(const QModelIndex& startIndex, int count); //generate the QPixmap thumbnails for a given set of pictures

private:
   QHash<QString, QPixmap*> mThumbnails; //stores the QPixmap* thumbnails using the filepath for the key

};

#endif // THUMBNAILPROXYMODEL_H
