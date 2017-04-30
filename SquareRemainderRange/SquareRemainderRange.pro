#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T11:07:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = Torus2D
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    torus2d.cpp \
    colorwidget.cpp \
    tilingwidget.cpp \
    graphwidget.cpp \
    tikzexport.cpp

HEADERS  += mainwindow.h \
    torus2d.h \
    colorwidget.h \
    RigidTransformation2D.h \
    tilingwidget.h \
    graphwidget.h \
    tikzexport.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -lDGtal
