#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T19:05:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = thread_proof
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tobii.cpp \
    fatigue.cpp

HEADERS  += mainwindow.h \
    tobii.h \
    fatigue.h

FORMS    += mainwindow.ui
