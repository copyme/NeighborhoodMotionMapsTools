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


# using shell_path() to correct path depending on platform
# escaping quotes and backslashes for file paths
copydata.commands = $(COPY_DIR) \"$$shell_path($$PWD\\doc)\" \"$$shell_path($$OUT_PWD)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata


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

RESOURCES +=
