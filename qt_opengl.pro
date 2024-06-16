QT += core gui widgets opengl

CONFIG += c++11

TARGET = OpenGLTriangle
TEMPLATE = app

# Source and header files
SOURCES += main.cpp \
           mainwindow.cpp \
           myopenglwidget.cpp

HEADERS += mainwindow.h \
           myopenglwidget.h

FORMS += mainwindow.ui

# Qt5OpenGL lib is explicit

# debug or release build
CONFIG(debug, debug|release) {
    DESTDIR = debug_build
} else {
    DESTDIR = release_build
}

