#-------------------------------------------------
#
# Project created by QtCreator 2018-05-29T16:34:01
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = headshot
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
        mainwindow.cpp \
    objetivo.cpp \
    proyectil.cpp \
    objetivograf.cpp \
    proyectorgraf.cpp \
    proyector.cpp \
    proyectilgraf.cpp \
    obstaculo.cpp \
    obstaculograf.cpp

HEADERS += \
        mainwindow.h \
    objetivo.h \
    proyectil.h \
    objetivograf.h \
    proyectorgraf.h \
    proyector.h \
    proyectilgraf.h \
    obstaculo.h \
    obstaculograf.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    images.qrc
