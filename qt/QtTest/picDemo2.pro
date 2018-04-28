#-------------------------------------------------
#
# Project created by QtCreator 2017-12-06T17:25:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picDemo2
TEMPLATE = app


SOURCES += main.cpp\
        basewidget.cpp \
    screenutils.cpp \
    menuwidget.cpp \
    pictureview.cpp \
    kinectimpl.cpp \
    pictureutils.cpp \
    widget.cpp \
    gesturecanvas.cpp \
    gestureview.cpp

HEADERS  += basewidget.h \
    screenutils.h \
    menuwidget.h \
    pictureview.h \
    kinectimpl.h \
    pictureutils.h \
    widget.h \
    gesturecanvas.h \
    gestureview.h


LIBS += "..\..\Kinect SDK\Lib\x64\Kinect20.lib"
LIBS += "..\..\KinectGestureLib\Bin\x64\Debug\KinectGesture_Debug.lib"
LIBS += "..\..\sgr\sgrLib\Windows\x64\sgrd.lib"
#LIBS += -L "C:\OpenCV\opencv\build\x64\vc12\lib"

DEPENDPATH +="..\..\openCV\lib\x64"

INCLUDEPATH += "..\..\KinectGestureLib\Include"
INCLUDEPATH += "..\..\openCV\inc"
INCLUDEPATH += "..\..\Kinect SDK\inc"
INCLUDEPATH += "..\..\sgr\sgrLib"
