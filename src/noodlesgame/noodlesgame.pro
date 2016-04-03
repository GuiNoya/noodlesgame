QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = noodlesgame
TEMPLATE = app

CONFIG += c++11
CONFIG += console

QMAKE_CXXFLAGS += -Winline

SOURCES += main.cpp\
    Room.cpp \
    Item.cpp \
    Gateway.cpp \
    Player.cpp \
    Event.cpp \
    ZorkFlee.cpp

HEADERS  += \
    Room.h \
    Item.h \
    Gateway.h \
    Player.h \
    Event.h \
    Defines.h \
    ZorkFlee.h

DISTFILES +=

RESOURCES +=
