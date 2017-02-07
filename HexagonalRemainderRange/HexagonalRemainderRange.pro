#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T13:42:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = Torus2DHexagonalGrid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        torus2d.cpp \
        tilingwidget.cpp

HEADERS  += mainwindow.h \
            torus2d.h \
            RigidTransformation3D.h \
            tilingwidget.h \
            hextools.h

FORMS    += mainwindow.ui

LIBS += -lDGtal
