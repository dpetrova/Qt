#include "albummodel.h"

using namespace std;

AlbumModel::AlbumModel(QObject* parent) :
    QAbstractListModel(parent),
    mDatabaseManager(DatabaseManager::instance()), //initialized with the DatabaseManager singleton address
    mAlbums(mDatabaseManager.albumDao.albums()) //if there are any stored albums in the database, mAlbums is immediately filled with those
{
}

//creation of a new album
QModelIndex AlbumModel::addAlbum(const Album& album)
{
    int rowIndex = rowCount(); //what will be the index of this new album (as start count from 0, the next index will be == length)

    //wrap real data modifications

    //first parameter of the beginInsertRows() function is the parent for this new element
    //the root for a model is always an empty QModelIndex() constructor, because we do not handle any hierarchical relationship
    //following parameters are the first and last modified indexes, as we insert a single element per call, they are same
    beginInsertRows(QModelIndex(), rowIndex, rowIndex); //nforms that rows are about to change for the given indexes
    unique_ptr<Album> newAlbum(new Album(album)); //create a copy of the album row
    mDatabaseManager.albumDao.addAlbum(*newAlbum); //insert new object into the database
    mAlbums->push_back(move(newAlbum)); //added new object to mAlbums and its ownership is transferred
    endInsertRows(); //informs that rows have been changed

     //end of wrap

    return index(rowIndex, 0);
}

//how many items are available
int AlbumModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent); //when a parameter of the function is not used
    return mAlbums->size();
}

//ask for data with two parameters: an index and a role
QVariant AlbumModel::data(const QModelIndex& index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const Album& album = *mAlbums->at(index.row()); //view asked for data at a specific index

    //role parameter associates each data element to a tag for the view to know what category of data is shown
    //switch on the role parameter tells us what data category should be returned
    switch (role) {
        case Roles::IdRole:
            return album.getId();
        case Roles::NameRole:
        case Qt::DisplayRole:
            return album.getName();
        default:
            return QVariant(); //something like an universal var in C#
    }
}

//view wants to update the data
bool AlbumModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!isIndexValid(index) || role != Roles::NameRole) { //only possible value to edit is the name, so the role is NameRole
        return false;
    }
    Album& album = *mAlbums->at(index.row());
    album.setName(value.toString());
    mDatabaseManager.albumDao.updateAlbum(album);
    emit dataChanged(index, index); //emit dataChanged() signal to notify whoever is interested that a row changed for the given indexes (the start index and end index)
    return true; //indicates if the data update was successful (in production app, should test the database processing success and return the relevant value)
}

//remove items, providing the starting row, the number of rows to delete, and the parent of the row
bool AlbumModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount())
    {
        return false;
    }

    //wrap the removal
    beginRemoveRows(parent, row, row + count - 1); //function, which expects the parent, starting index, and last index
    int countLeft = count;
    while (countLeft--) //loop on the rows left to delete
    {
        const Album& album = *mAlbums->at(row + countLeft);
        mDatabaseManager.albumDao.removeAlbum(album.id()); //delete it from the database
    }
    mAlbums->erase(mAlbums->begin() + row, mAlbums->begin() + row + count); //remove from mAlbums
    endRemoveRows();
    //end wrap

    return true;
}

//provides some meta-information about the data structure, so the role names to be accessed via QML
QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::IdRole] = "id";
    roles[Roles::NameRole] = "name";
    return roles;
}

bool AlbumModel::isIndexValid(const QModelIndex& index) const
{
    if (index.row() < 0 || index.row() >= rowCount() || !index.isValid())
    {
        return false;
    }
    return true;
}
