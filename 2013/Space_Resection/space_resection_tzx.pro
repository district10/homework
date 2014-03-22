#-------------------------------------------------
#
# Project created by QtCreator 2013-09-26T19:55:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = space_resection_tzx
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    space_resection_tzx.cpp \
    point_2d.cpp \
    point_3d.cpp \
    matrix.cpp \
    exception.cpp

HEADERS += \
    space_resection_tzx.h \
    point_2d.h \
    point_3d.h \
    matrix.h \
    exception.h

RESOURCES += \
    space_resection_data.qrc
