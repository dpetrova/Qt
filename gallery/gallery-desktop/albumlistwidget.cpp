#include "albumlistwidget.h"
#include "ui_albumlistwidget.h"

#include <QInputDialog>

#include "albummodel.h"

AlbumListWidget::AlbumListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListWidget),
    mAlbumModel(nullptr)
{
    ui->setupUi(this);
    connect(ui->createAlbumButton, &QPushButton::clicked, this, &AlbumListWidget::createAlbum);
}

AlbumListWidget::~AlbumListWidget()
{
    delete ui;
}

//set the model of the albumList
void AlbumListWidget::setModel(AlbumModel* model)
{
    mAlbumModel = model;
    ui->albumListView->setModel(mAlbumModel);
}

//set the selection model of the albumList
void AlbumListWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
    ui->albumListView->setSelectionModel(selectionModel);
}

void AlbumListWidget::createAlbum()
{
    if(!mAlbumModel) {
        return;
    }

    bool ok;
    QString albumName = QInputDialog::getText(this,
                                              "Create a new Album",
                                              "Choose a name",
                                              QLineEdit::Normal,
                                              "New album",
                                              &ok);

    if (ok && !albumName.isEmpty())
    {
        Album album(albumName);
        QModelIndex createdIndex = mAlbumModel->addAlbum(album); //create and store the real object with a unique ID
        ui->albumListView->setCurrentIndex(createdIndex);
    }
}
