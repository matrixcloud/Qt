#-------------------------------------------------
#
# Project created by QtCreator 2014-05-05T22:32:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyNotepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    fileutil.cpp \
    finddialog.cpp \
    codeeditor.cpp

HEADERS  += mainwindow.h \
    about.h \
    fileutil.h \
    finddialog.h \
    codeeditor.h

FORMS    += mainwindow.ui \
    about.ui \
    finddialog.ui

RESOURCES += \
    res.qrc
