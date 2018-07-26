#-------------------------------------------------
#
# Project created by QtCreator 2018-07-25T12:07:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sqlite_db
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        login.cpp \
    createemployee.cpp

HEADERS += \
        login.h \
    createemployee.h

FORMS += \
        login.ui \
    createemployee.ui
