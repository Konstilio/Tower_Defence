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
    gamestatewidget.cpp \
    resultinfodialog.cpp

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
    gamestatewidget.h \
    resultinfodialog.h

FORMS    += widget.ui \
    userstatuswidget.ui \
    userbuildmenuwidget.ui \
    iteminfowidget.ui \
    gamestatewidget.ui \
    resultinfodialog.ui

RESOURCES += \
    resources.qrc

win32 {

contains(QT_ARCH, i386) {
    message("32-bit")
} else {
    CONFIG(debug, debug|release) {
        Qt5Cored.commands = copy /Y %QTDIR%\\bin\\Qt5Cored.dll debug
        Qt5Cored.target = debug/Qt5Cored.dll
        Qt5Guid.commands = copy /Y %QTDIR%\\bin\\Qt5Guid.dll debug
        Qt5Guid.target = debug/Qt5Guid.dll
        Qt5Widgetsd.commands = copy /Y %QTDIR%\\bin\\Qt5Widgetsd.dll debug
        Qt5Widgetsd.target = debug/Qt5Widgetsd.dll

        QMAKE_EXTRA_TARGETS += Qt5Cored Qt5Guid Qt5Widgetsd
        POST_TARGETDEPS += debug/Qt5Cored.dll debug/Qt5Guid.dll debug/Qt5Widgetsd.dll
    } else:CONFIG(release, debug|release) {
        Qt5Core.commands = copy /Y %QTDIR%\\bin\\Qt5Core.dll release
        Qt5Core.target = release/Qt5Core.dll
        Qt5Gui.commands = copy /Y %QTDIR%\\bin\\Qt5Gui.dll release
        Qt5Gui.target = release/Qt5Gui.dll
        Qt5Widgets.commands = copy /Y %QTDIR%\\bin\\Qt5Widgets.dll release
        Qt5Widgets.target = release/Qt5Widgets.dll

        QMAKE_EXTRA_TARGETS += Qt5Core Qt5Gui Qt5Widgets
        POST_TARGETDEPS += release/Qt5Core.dll release/Qt5Gui.dll release/Qt5Widgets.dll
    } else {
        error(Unknown set of dependencies.)
    }
}


}
macx {
    copyfiles.commands = cp -r $$PWD/Images $$OUT_PWD/$$TARGET\.app/Contents/Resources
    macdeployqt.commands = macdeployqt $$OUT_PWD/$$TARGET\.app -dmg -verbose=2

    QMAKE_EXTRA_TARGETS += copyfiles
    QMAKE_EXTRA_TARGETS += macdeployqt
    POST_TARGETDEPS += copyfiles
    POST_TARGETDEPS += macdeployqt
}

