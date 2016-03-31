#-------------------------------------------------
#
# Project created by QtCreator 2016-03-18T20:24:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qthgame
TEMPLATE = app

CONFIG += c++11
CONFIG += console

QMAKE_CXXFLAGS += -Winline

SOURCES += main.cpp\
    Room.cpp \
    ZorkUL.cpp \
    Item.cpp \
    Gateway.cpp \
    Player.cpp \
    Event.cpp

HEADERS  += \
    Room.h \
    ZorkUL.h \
    Item.h \
    Gateway.h \
    Player.h \
    Event.h \
    Defines.h

DISTFILES +=

RESOURCES +=
