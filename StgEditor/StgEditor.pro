#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T14:08:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StgEditor
TEMPLATE = app


SOURCES += main.cpp\
        texturetab.cpp \
        mainwindow.cpp \
    editordata.cpp \
    optiondialog.cpp


HEADERS  += texturetab.h \
        mainwindow.h \
    editordata.h \
    optiondialog.h


FORMS    += texturetab.ui\
        mainwindow.ui \
        optiondialog.ui

