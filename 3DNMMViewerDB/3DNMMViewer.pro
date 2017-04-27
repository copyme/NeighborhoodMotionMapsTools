#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T22:15:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = 3DNMMViewer
TEMPLATE = app


SOURCES += main.cpp\
        CSVExtractor.cpp\
        mainwindow.cpp \
    nmm3dpainter.cpp \
    pixel.cpp

HEADERS  += mainwindow.h\
            CSVExtractor.h \
    nmm3dpainter.h \
    pixel.h

FORMS    += mainwindow.ui \
    nmm3dpainter.ui \
    pixel.ui
