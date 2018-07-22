#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>
#include <QItemSelection>

namespace Ui {
class PictureWidget;
}

class PictureModel;
class QItemSelectionModel;
class ThumbnailProxyModel;

class PictureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PictureWidget(QWidget *parent = 0);
    ~PictureWidget();
    void setModel(ThumbnailProxyModel* model); //ThumbnailProxyModel* setter
    void setSelectionModel(QItemSelectionModel* selectionModel); //QItemSelectionModel* setter

signals:
    void backToGallery(); //triggered when the user clicks on the backButton
protected:
    //override resizeEvent() to ensure that we always use all the visible area to display the picture
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void deletePicture(); //process the deletion when the user clicks on deletePictureButton
    void loadPicture(const QItemSelection& selected); //to update the UI with the specified picture

private:
    void updatePicturePixmap(); //helper function to display the picture according to the current widget size

private:
    Ui::PictureWidget* ui;
    ThumbnailProxyModel* mModel;
    QItemSelectionModel* mSelectionModel;
    QPixmap mPixmap;
};

#endif // PICTUREWIDGET_H
