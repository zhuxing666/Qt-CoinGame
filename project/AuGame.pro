#-------------------------------------------------
#
# Project created by QtCreator 2021-08-30T16:16:13
#
#-------------------------------------------------
QT       += core
QT       += core gui
CONFIG   += c++11
QT       += core gui multimedia



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AuGame
TEMPLATE = app


SOURCES += main.cpp\
        mainscence.cpp \
    mypushbutton.cpp \
    chooselevelscenece.cpp \
    playscene.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS  += mainscence.h \
    mypushbutton.h \
    chooselevelscenece.h \
    playscene.h \
    mycoin.h \
    dataconfig.h

FORMS    += mainscence.ui

RESOURCES += \
    res.qrc
