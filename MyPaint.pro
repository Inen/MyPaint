#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T21:19:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPaint
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    paintwidget.cpp

HEADERS  += mainwindow.h \
    paintwidget.h

FORMS    += mainwindow.ui

QMAKE_LFLAGS += -static -static-libgcc

RESOURCES += \
    Resources.qrc
