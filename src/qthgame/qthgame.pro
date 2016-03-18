#-------------------------------------------------
#
# Project created by QtCreator 2016-03-18T20:24:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qthgame
TEMPLATE = app

SOURCES += main.cpp\
    gamewindow.cpp \
    item.cpp \
    Character.cpp \
    Command.cpp \
    CommandWords.cpp \
    Parser.cpp \
    Room.cpp \
    ZorkUL.cpp

HEADERS  += gamewindow.h \
    item.h \
    Character.h \
    Command.h \
    CommandWords.h \
    Parser.h \
    Room.h \
    ZorkUL.h
