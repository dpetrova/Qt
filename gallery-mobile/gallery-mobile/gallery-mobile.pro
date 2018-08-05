TEMPLATE = app

QT += qml quick sql svg

CONFIG += c++11

SOURCES += main.cpp \
    PictureImageProvider.cpp

RESOURCES += gallery.qrc

#LIBS += -L$$OUT_PWD/../gallery-core/ -lgallery-core
#INCLUDEPATH += $$PWD/../gallery-core
#DEPENDPATH += $$PWD/../gallery-core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/release/ -lgallery-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/debug/ -lgallery-core

INCLUDEPATH += $$PWD/../gallery-core
DEPENDPATH += $$PWD/../gallery-core

HEADERS += \
    PictureImageProvider.h

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_EXTRA_LIBS = \
        $$[QT_INSTALL_LIBS]/libQt5Sql.so
}


