#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T12:52:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oko
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    funcs.cpp \
    generatorData.cpp \
    controllerData.cpp

HEADERS  += mainwindow.h \
    funcs.h \
    generatorData.h \
    controllerData.h

FORMS    += mainwindow.ui
