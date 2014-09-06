#-------------------------------------------------
#
# Project created by QtCreator 2014-05-19T12:57:03
#
#-------------------------------------------------

QT       += core gui
QT       += webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NanjingChannel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    saversettingdialog.cpp \
    screensaver.cpp

HEADERS  += mainwindow.h \
    saversettingdialog.h \
    constant.h \
    screensaver.h

FORMS    += mainwindow.ui \
    saversettingdialog.ui \
    screensaver.ui
