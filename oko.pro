#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T12:52:31
#
#-------------------------------------------------

QT       += core gui bluetooth
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = oko
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    lib/qcustomplot/qcustomplot.cpp

HEADERS  += src/mainwindow.h \
    lib/qcustomplot/qcustomplot.h

FORMS    += src/mainwindow.ui
