#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "gallery-core_global.h"
#include "album.h"
#include "databasemanager.h"

using namespace std;

class GALLERYCORESHARED_EXPORT AlbumModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
    };

    AlbumModel(QObject* parent = 0);

    QModelIndex addAlbum(const Album& album);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override; //get the list size
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override; //get a specific piece of information about the data to display
    bool setData(const QModelIndex& index, const QVariant& value, int role) override; //used to update data
    bool removeRows(int row, int count, const QModelIndex& parent) override; //used to remove data
    QHash<int, QByteArray> roleNames() const override; //indicate to the framework the name for each "role"

private:
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& mDatabaseManager; //link to the database. In the Model/View schema, the model will communicate with the data layer through it
    unique_ptr<vector<unique_ptr<Album>>> mAlbums; //acts as a buffer that will avoid hitting the database too much
};

#endif // ALBUMMODEL_H
