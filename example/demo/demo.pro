QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app
SOURCES += \
    main.cpp \
    Widget.cpp

HEADERS += \
    Widget.h

include(../../QxtGlobalShortcut.pri)
