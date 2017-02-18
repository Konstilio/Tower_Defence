#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T18:26:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tower_Defence
TEMPLATE = app

CONFIG += c++11
CONFIG += -Wno-inconsistent-missing-override

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    gameview.cpp \
    gamescene.cpp \
    tower.cpp \
    userstatuswidget.cpp \
    generalutils.cpp \
    userbuildmenuwidget.cpp \
    gameviewstate.cpp \
    ammo.cpp \
    tilegraph.cpp \
    enemy.cpp \
    level.cpp \
    iteminfowidget.cpp \
    gamestatewidget.cpp

HEADERS  += widget.h \
    gameview.h \
    gamescene.h \
    tower.h \
    userstatuswidget.h \
    generalutils.h \
    userbuildmenuwidget.h \
    gameviewstate.h \
    ammo.h \
    tilegraph.h \
    enemy.h \
    level.h \
    iteminfowidget.h \
    gamestatewidget.h

FORMS    += widget.ui \
    userstatuswidget.ui \
    userbuildmenuwidget.ui \
    iteminfowidget.ui \
    gamestatewidget.ui

RESOURCES += \
    resources.qrc
