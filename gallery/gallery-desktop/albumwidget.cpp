#include "albumwidget.h"
#include "ui_albumwidget.h"

#include <QInputDialog>
#include <QFileDialog>

#include "albummodel.h"
#include "picturemodel.h"
#include "thumbnailproxymodel.h"

#include "PictureDelegate.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget),
    mAlbumModel(nullptr),
    mAlbumSelectionModel(nullptr),
    mPictureModel(nullptr),
    mPictureSelectionModel(nullptr)
{
    ui->setupUi(this);
    clearUi();

    //configures thumbnailListView, our QListView that will display thumbnails of the current selected album
    ui->thumbnailListView->setSpacing(5); //by default items are glued to each other; you can add spacing between them
    ui->thumbnailListView->setResizeMode(QListView::Adjust); //dynamically lays out items when the view is resized
    ui->thumbnailListView->setFlow(QListView::LeftToRight); //specifies the list direction
    ui->thumbnailListView->setWrapping(true); //allows an item to wrap when there is not enough space to display it in the visible area
    ui->thumbnailListView->setItemDelegate(new PictureDelegate(this));

    //all the signal connections related to the UI
    connect(ui->thumbnailListView, &QListView::doubleClicked, this, &AlbumWidget::pictureActivated);
    connect(ui->deleteAlbumButton, &QPushButton::clicked, this, &AlbumWidget::deleteAlbum);
    connect(ui->editAlbumButton, &QPushButton::clicked, this, &AlbumWidget::editAlbum);
    connect(ui->addPicturesButton, &QPushButton::clicked, this, &AlbumWidget::addPictures);
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

//albumModel setter
void AlbumWidget::setAlbumModel(AlbumModel* albumModel)
{
    mAlbumModel = albumModel;

    //if the selected album's data changed, we need to update the UI with the loadAlbum() function
    connect(mAlbumModel, &QAbstractItemModel::dataChanged, [this] (const QModelIndex &topLeft) {
        if (topLeft == mAlbumSelectionModel->currentIndex())
        {
            loadAlbum(topLeft);
        }
    });
}

//albumSelectionModel setter
void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel)
{
    mAlbumSelectionModel = albumSelectionModel;

    //AlbumWidget component must update its UI according to the currently selected album
    //each time user selects an album from AlbumListWidget, the signal QItemSelectionModel::selectionChanged is triggered
    connect(mAlbumSelectionModel, &QItemSelectionModel::selectionChanged, [this](const QItemSelection &selected) {
        //if the selection is  empty, we simply clear the UI
        if (selected.isEmpty())
        {
            clearUi();
            return;
        }
        loadAlbum(selected.indexes().first()); //update the UI (as we do not support album multi-selection, we can restrict the process to the first selected element)
    });
}

//pictureModel setter
void AlbumWidget::setPictureModel(ThumbnailProxyModel* pictureModel)
{
    mPictureModel = pictureModel;
    ui->thumbnailListView->setModel(pictureModel);
}

//selectionModel of thumbnailListView setter
void AlbumWidget::setPictureSelectionModel(QItemSelectionModel* selectionModel)
{
    ui->thumbnailListView->setSelectionModel(selectionModel);
}

//delete album
void AlbumWidget::deleteAlbum()
{
    if (mAlbumSelectionModel->selectedIndexes().isEmpty())
    {
        return;
    }
    int row = mAlbumSelectionModel->currentIndex().row(); //retrieve the current row index from mAlbumSelectionModel
    mAlbumModel->removeRow(row); //request mAlbumModel to delete this row

    // Try to select the previous album
    QModelIndex previousModelIndex = mAlbumModel->index(row - 1, 0);
    if(previousModelIndex.isValid())
    {
        mAlbumSelectionModel->setCurrentIndex(previousModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }

    // Try to select the next album
    QModelIndex nextModelIndex = mAlbumModel->index(row, 0);
    if(nextModelIndex.isValid())
    {
        mAlbumSelectionModel->setCurrentIndex(nextModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }
}

//edit album
void AlbumWidget::editAlbum()
{
    if (mAlbumSelectionModel->selectedIndexes().isEmpty())
    {
        return;
    }
    QModelIndex currentAlbumIndex = mAlbumSelectionModel->selectedIndexes().first(); //get album index
    QString oldAlbumName = mAlbumModel->data(currentAlbumIndex, AlbumModel::Roles::NameRole).toString(); //get the current name from album model

    //generate an input dialog
    bool ok;
    QString newName = QInputDialog::getText(this,
                                            "Album's name",
                                            "Change Album name",
                                            QLineEdit::Normal,
                                            oldAlbumName,
                                            &ok);

    if (ok && !newName.isEmpty())
    {
        mAlbumModel->setData(currentAlbumIndex, newName, AlbumModel::Roles::NameRole); //request the album model to update the name
        //we do not directly update UI; this will be automatically performed because setData() emits a signal, dataChanged(), which AlbumWidget handles
    }
}

//add pictures
void AlbumWidget::addPictures()
{
    //QFileDialog class is used here to help the user select several picture files
    QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                          "Add pictures",
                                                          QDir::homePath(),
                                                          "Picture files (*.jpg *.png)");
    if (!filenames.isEmpty())
    {
        QModelIndex lastModelIndex;
        for (auto filename : filenames)
        {
            Picture picture(filename); //create a Picture data holder
            //request mPictureModel to add this picture in the current album
            //because mPictureModel is a ThumbnailProxyModel class, we have to retrieve the real PictureModel using the helper function, pictureModel()
            lastModelIndex = mPictureModel->pictureModel()->addPicture(picture);
        }
        ui->thumbnailListView->setCurrentIndex(lastModelIndex); //elect the most recently added picture in thumbnailListView
    }
}

//clears the album's name and hides the buttons,
//while the loadAlbum() function retrieves the Qt::DisplayRole (the album's name) and displays the buttons
void AlbumWidget::clearUi()
{
    ui->albumNameLabel->setText("");
    ui->deleteAlbumButton->setVisible(false);
    ui->editAlbumButton->setVisible(false);
    ui->addPicturesButton->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex& albumIndex)
{
    mPictureModel->pictureModel()->setAlbumId(mAlbumModel->data(albumIndex, AlbumModel::Roles::IdRole).toInt());
    ui->albumNameLabel->setText(mAlbumModel->data(albumIndex, Qt::DisplayRole).toString());
    ui->deleteAlbumButton->setVisible(true);
    ui->editAlbumButton->setVisible(true);
    ui->addPicturesButton->setVisible(true);
}
