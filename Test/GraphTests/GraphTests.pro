QT += widgets testlib
QT += core gui

TARGET = GraphTests
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
CONFIG += -Wno-inconsistent-missing-override

TEMPLATE = app

SOURCES += main.cpp \
    ../../tilegraph.cpp \
    graphtests.cpp

HEADERS += \
    ../../tilegraph.h \
    graphtests.h

