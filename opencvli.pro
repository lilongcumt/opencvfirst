#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T22:18:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvli
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageprocess.cpp

HEADERS  += mainwindow.h \
    imageprocess.h

FORMS    += mainwindow.ui

include(opencvconfig.pri)
