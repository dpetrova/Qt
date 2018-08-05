#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include "AlbumModel.h"
#include "PictureModel.h"
#include "PictureImageProvider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AlbumModel albumModel;
    PictureModel pictureModel(albumModel);

    QQmlApplicationEngine engine;

    //our models will be instantiated in C++ and exposed to QML using the root QQmlContext object
    QQmlContext* context = engine.rootContext();
    //function setContextProperty() allows us to bind a C++ QObject to a QML property
    //first argument will be the QML property name
    context->setContextProperty("thumbnailSize", PictureImageProvider::THUMBNAIL_SIZE.width());
    context->setContextProperty("albumModel", &albumModel);
    context->setContextProperty("pictureModel", &pictureModel);

    engine.addImageProvider("pictures", new PictureImageProvider(&pictureModel)); //add image provider to QML engine
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml"))); //entry point

    return app.exec();
}
