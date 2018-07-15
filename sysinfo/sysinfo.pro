#-------------------------------------------------
#
# Project created by QtCreator 2018-07-15T14:06:48
#
#-------------------------------------------------

QT       += core gui charts
CONFIG += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysinfo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# remove specific platform source and header files from SOURCES and HEADERS, and put it into windows/linux sections
# so when building for other platforms thise file cannot be processed by qmake
# that is why we can safely include a specific header such as windows.h without harming the compilation on other platforms
SOURCES += \
        main.cpp \
        mainwindow.cpp \
        sysinfo.cpp \
    sysinfowidget.cpp \
    cpuwidget.cpp

HEADERS += \
        mainwindow.h \
        sysinfo.h \
    sysinfowidget.h \
    cpuwidget.h

windows {
    SOURCES += sysinfowindows.cpp
    HEADERS += sysinfowindows.h
}

linux {
    SOURCES += sysinfolinux.cpp
    HEADERS += sysinfolinux.h
}

FORMS += \
        mainwindow.ui
