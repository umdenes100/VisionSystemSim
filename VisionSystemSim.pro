#-------------------------------------------------
#
# Project created by QtCreator 2018-02-14T18:18:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += serialport
QT += network
CONFIG += openssl-linked

TARGET = VisionSystemSim
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


SOURCES += \
        main.cpp \
    arena.cpp \
    settingswidget.cpp \
    communicationwidget.cpp \
    osv.cpp \
    osveditorwindow.cpp \
    editorbutton.cpp \
    mainwindow.cpp \
    controller.cpp \
    response.cpp

HEADERS += \
        mainwindow.h \
    arena.h \
    settingswidget.h \
    communicationwidget.h \
    osv.h \
    detail.h \
    osveditorwindow.h \
    editorbutton.h \
    controller.h \
    response.h

FORMS += \
        mainwindow.ui \
    arena.ui \
    settingswidget.ui \
    communicationwidget.ui \
    osveditorwindow.ui \
    editorbutton.ui
