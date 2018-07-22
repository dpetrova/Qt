#include "thumbnailproxymodel.h"

#include "picturemodel.h"

const unsigned int THUMBNAIL_SIZE = 350;

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent) :
    QIdentityProxyModel(parent),
    mThumbnails()
{
}

QVariant ThumbnailProxyModel::data(const QModelIndex& index, int role) const
{
    //for any role that is not Qt::DecorationRole, the parent class data() is called
    if (role != Qt::DecorationRole) {
        return QIdentityProxyModel::data(index, role);
    }

    QString filepath = sourceModel()->data(index, PictureModel::Roles::FilePathRole).toString(); //get filepath of the picture referenced by the index
    return *mThumbnails[filepath]; //return the QPixmap object of mThumbnails
}

//ThumbnailProxyModel class is configured to know which base model should be proxied
void ThumbnailProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
    if (!sourceModel) {
        return;
    }

    //register lambdas to two signals emitted by the original model

    //modelReset signal is triggered when pictures should be loaded for a given album
    connect(sourceModel, &QAbstractItemModel::modelReset, [this] {
        reloadThumbnails();
    });

    //rowsInserted signal is triggered each time new pictures are added
    connect(sourceModel, &QAbstractItemModel::rowsInserted, [this](const QModelIndex& parent, int first, int last) {
        generateThumbnails(index(first, 0), last - first + 1);
    });
}

//classes that will interact with ThumbnailProxyModel will need to call some functions that are specific to PictureModel to create or delete pictures
//helper function to centralize the cast of the sourceModel to PictureModel*
PictureModel* ThumbnailProxyModel::pictureModel() const
{
    return static_cast<PictureModel*>(sourceModel());
}

//each time that an album is loaded, we should clear the content of the mThumbnails class and load the new pictures
void ThumbnailProxyModel::reloadThumbnails()
{
    qDeleteAll(mThumbnails);
    mThumbnails.clear();
    generateThumbnails(index(0, 0), rowCount());
}

//generates the thumbnails for a given range indicated by the parameters (startIndex and count)
void ThumbnailProxyModel::generateThumbnails(const QModelIndex& startIndex, int count)
{
    if (!startIndex.isValid()) {
        return;
    }

    const QAbstractItemModel* model = startIndex.model();
    int lastIndex = startIndex.row() + count;
    for(int row = startIndex.row(); row < lastIndex; row++)
    {
        QString filepath = model->data(model->index(row, 0), PictureModel::Roles::FilePathRole).toString(); //retrieve the filepath from the original model
        QPixmap pixmap(filepath);
        //generate a downsized QPixmap
        auto thumbnail = new QPixmap(pixmap.scaled(THUMBNAIL_SIZE,
                                                   THUMBNAIL_SIZE, //scaled down to this size
                                                   Qt::KeepAspectRatio, //espects the aspect ratio of the original picture
                                                   Qt::SmoothTransformation));
        mThumbnails.insert(filepath, thumbnail); //insert in mThumbnails QHash
    }
}
