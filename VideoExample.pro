#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T19:40:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoExample
TEMPLATE = app

SOURCES += main.cpp\
        mymainwindow.cpp \
    cvimagewidget.cpp \
    videodata.cpp \
    controller.cpp

HEADERS  += mymainwindow.h \
    cvimagewidget.h \
    videodata.h \
    controller.h

FORMS    += mymainwindow.ui

INCLUDEPATH += E:\\7.DEP\\OpenCV_3.1.0\\opencv\\build\\include
LIBS += -LE:\\7.DEP\\OpenCV_3.1.0\\opencv\\build\\x64\\vc12\\lib \
    opencv_world310d.lib

RESOURCES +=


