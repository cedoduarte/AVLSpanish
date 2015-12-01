#-------------------------------------------------
#
# Project created by QtCreator 2015-11-26T14:31:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AVLExcentaExamen
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AVL.cpp

HEADERS  += MainWindow.h \
    AVL.h

FORMS    += MainWindow.ui

QMAKE_CXXFLAGS += -std=gnu++14
