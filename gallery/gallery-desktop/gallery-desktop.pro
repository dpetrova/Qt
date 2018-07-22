QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gallery-desktop
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    albumlistwidget.cpp \
    thumbnailproxymodel.cpp \
    albumwidget.cpp \
    picturedelegate.cpp \
    picturewidget.cpp \
    gallerywidget.cpp

HEADERS += \
        mainwindow.h \
    albumlistwidget.h \
    thumbnailproxymodel.h \
    albumwidget.h \
    picturedelegate.h \
    picturewidget.h \
    gallerywidget.h

FORMS += \
        mainwindow.ui \
    albumlistwidget.ui \
    albumwidget.ui \
    picturewidget.ui \
    gallerywidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/release/ -lgallery-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/debug/ -lgallery-core
else:unix: LIBS += -L$$OUT_PWD/../gallery-core/ -lgallery-core

INCLUDEPATH += $$PWD/../gallery-core
DEPENDPATH += $$PWD/../gallery-core

RESOURCES += \
    resources.qrc
