#include <QGuiApplication>
#include <QtGui/QOpenGLContext>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //qputenv("QT3D_GLSL100_WORKAROUND", ""); //this instruction is a workaround related to Qt3D shaders on some embedded Linux devices

    //configure a QSurfaceFormat to properly handle OpenGL
    QSurfaceFormat format;
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        format.setVersion(3, 2);
        format.setProfile(QSurfaceFormat::CoreProfile);
    }
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    //view will use QSurfaceFormat to paint itself
    QQuickView view;
    view.setFormat(format);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QObject::connect(view.engine(), &QQmlEngine::quit, &app, &QGuiApplication::quit); //connect Qt.quit() signal to the QGuiApplication::quit()
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
