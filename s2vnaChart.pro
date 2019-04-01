#-------------------------------------------------
#
# Project created by QtCreator 2019-03-28T16:11:36
#
#-------------------------------------------------

QT       += core gui charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = s2vnaChart
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawing.cpp

HEADERS  += mainwindow.h \
    drawing.h

FORMS    += mainwindow.ui
