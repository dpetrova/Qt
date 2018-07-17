#-------------------------------------------------
#
# Project created by QtCreator 2018-07-16T19:47:13
#
#-------------------------------------------------

QT       += sql

QT       -= gui #by default, QtGui is always included and has to be removed explicitly.

TARGET = gallery-core
TEMPLATE = lib #use lib template to tell qmake to generate a Makefile that will output a shared library named gallery-core (target)

DEFINES += GALLERYCORE_LIBRARY #compilation flag that lets the compiler know when it should import or export library symbols

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        album.cpp \
    picture.cpp \
    databasemanager.cpp \
    albumdao.cpp \
    picturedao.cpp

HEADERS += \
        album.h \
        gallery-core_global.h \ #generated header; this file is syntactic sugar provided by Qt to ease the pain of a cross-platform library
    picture.h \
    databasemanager.h \
    albumdao.h \
    picturedao.h

