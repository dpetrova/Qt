#include "picturemodel.h"

#include "album.h"
#include "databasemanager.h"
#include "albummodel.h"

using namespace std;

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
    QAbstractListModel(parent),
    mDatabaseManager(DatabaseManager::instance()),
    mAlbumId(-1),
    mPictures(new vector<unique_ptr<Picture>>())
{
    //picture should be deleted if the owning album is deleted
    //this will be done automatically when AlbumModel emits the rowsRemoved signal
    connect(&albumModel, &AlbumModel::rowsRemoved, this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture& picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    unique_ptr<Picture>newPicture(new Picture(picture));
    mDatabaseManager.pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
    mPictures->push_back(move(newPicture));
    endInsertRows();
    return index(rows, 0);
}

int PictureModel::rowCount(const QModelIndex& /*parent*/) const
{
    return mPictures->size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const Picture& picture = *mPictures->at(index.row());
    switch (role) {
        case Qt::DisplayRole:
            return picture.getFileUrl().fileName();
            break;
        case Roles::UrlRole:
            return picture.getFileUrl();
            break;
        case Roles::FilePathRole:
            return picture.getFileUrl().toLocalFile();
            break;
        default:
            return QVariant();
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount())
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while(countLeft--)
    {
        const Picture& picture = *mPictures->at(row + countLeft);
        mDatabaseManager.pictureDao.removePicture(picture.id());
    }
    mPictures->erase(mPictures->begin() + row, mPictures->begin() + row + count);
    endRemoveRows();

    return true;
}

QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::FilePathRole] = "filepath";
    return roles;
}

//because we chose to restrict PictureModel to work on the pictures for a given album,
//we do not know at the construction of PictureModel which album to choose,
//so the loading can only be done when the album is selected
void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();
}

void PictureModel::clearAlbum()
{
    setAlbumId(-1);
}

void PictureModel::deletePicturesForAlbum()
{
    mDatabaseManager.pictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
}

void PictureModel::loadPictures(int albumId)
{
    if (albumId <= 0) {
        mPictures.reset(new vector<unique_ptr<Picture>>()); //if a negative album id is provided, we clear the pictures
        return;
    }
    mPictures = mDatabaseManager.pictureDao.picturesForAlbum(albumId); //assign the database pictures for the given albumId to mPictures
}

bool PictureModel::isIndexValid(const QModelIndex& index) const
{
    if (index.row() < 0 || index.row() >= rowCount() || !index.isValid())
    {
        return false;
    }
    return true;
}
