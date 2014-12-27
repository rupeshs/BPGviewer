#-------------------------------------------------
#
# Project created by QtCreator 2014-12-20T07:51:51
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = BPGviewer
TEMPLATE = app

INCLUDEPATH += qtsingleapplication
DEPENDPATH += qtsingleapplication
HEADERS += qtsingleapplication.h qtlocalpeer.h \
    imagescene.h \
    imageview.h

SOURCES += qtsingleapplication.cpp qtlocalpeer.cpp \
    imagescene.cpp \
    imageview.cpp

SOURCES += main.cpp\
        viewerwindow.cpp \
    qbetterportablegraphics.cpp \
    aboutdialog.cpp

HEADERS  += viewerwindow.h \
    qbetterportablegraphics.h \
    WinVersion.h \
    aboutdialog.h
FORMS    += viewerwindow.ui \
    aboutdialog.ui

LIBS     +=$$PWD/libbpg/libbpg.a
LIBS     +=$$PWD/libpng/lib/libpng.lib

RESOURCES += \
    BPGviewer.qrc

win32:RC_FILE = BPGviewer.rc


