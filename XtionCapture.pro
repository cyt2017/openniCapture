#-------------------------------------------------
#
# Project created by QtCreator 2017-09-03T10:00:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XtionCapture
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += /usr/lib/x86_64-linux-gnu/libopencv*.so
INCLUDEPATH+=/home/cyt/workspace/OpenNI2/Include /home/cyt/myLibs/include/pcl-1.8  /usr/include/eigen3  /home/cyt/myLibs/include/vtk-8.1  /usr/include/boost
LIBS+=/home/cyt/workspace/OpenNI2/Bin/x64-Release/libOpenNI2.so
