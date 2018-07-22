#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStackedWidget>
#include <QItemSelectionModel>

#include "GalleryWidget.h"
#include "PictureWidget.h"
#include "AlbumModel.h"
#include "PictureModel.h"
#include "ThumbnailProxyModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mGalleryWidget(new GalleryWidget(this)),
    mPictureWidget(new PictureWidget(this)),
    mStackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this); //initialize the UI

    AlbumModel* albumModel = new AlbumModel(this); //create AlbumModel
    QItemSelectionModel* albumSelectionModel = new QItemSelectionModel(albumModel, this); //create QItemSelectionModel
    //call the setters of GalleryWidget that will dispatch them to the AlbumListWidget and AlbumWidget objects
    mGalleryWidget->setAlbumModel(albumModel);
    mGalleryWidget->setAlbumSelectionModel(albumSelectionModel);

    PictureModel* pictureModel = new PictureModel(*albumModel, this);
    ThumbnailProxyModel* thumbnailModel = new ThumbnailProxyModel(this);
    thumbnailModel->setSourceModel(pictureModel);

    QItemSelectionModel* pictureSelectionModel = new QItemSelectionModel(thumbnailModel, this);
    mGalleryWidget->setPictureModel(thumbnailModel);
    mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
    mPictureWidget->setModel(thumbnailModel);
    mPictureWidget->setSelectionModel(pictureSelectionModel);

    //signal is emitted when you doubleclick on a thumbnail in albumWidget -> switch the display with the picture at its full size
    connect(mGalleryWidget, &GalleryWidget::pictureActivated, this, &MainWindow::displayPicture);
    //signal emitted when the user clicks on the backButton from PictureWidget -> it will switch again to display the gallery
    connect(mPictureWidget, &PictureWidget::backToGallery, this, &MainWindow::displayGallery);

    //add our two widgets, mGalleryWidget and mPictureWidget, to the mStackedWidget class
    mStackedWidget->addWidget(mGalleryWidget);
    mStackedWidget->addWidget(mPictureWidget);
    //when the application starts, we want to display the gallery, so we call our own slot displayGallery()
    displayGallery();

    //define mStackedWidget as the main window's central widget
    setCentralWidget(mStackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//switch to the display gallery
void MainWindow::displayGallery()
{
    mStackedWidget->setCurrentWidget(mGalleryWidget);
}

//switch to the display picture
void MainWindow::displayPicture(const QModelIndex& /*index*/)
{
    mStackedWidget->setCurrentWidget(mPictureWidget);
}
