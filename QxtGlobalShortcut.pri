DEFINES += QXT_STATIC

INCLUDEPATH += $$PWD/src/core
HEADERS += $$PWD/src/core/qxtglobal.h
SOURCES += $$PWD/src/core/qxtglobal.cpp

INCLUDEPATH += $$PWD/src/widgets

HEADERS += \
    $$PWD/src/widgets/qxtglobalshortcut.h
    $$PWD/src/widgets/qxtglobalshortcut_p.h

SOURCES += \
    $$PWD/src/widgets/qxtglobalshortcut.cpp

unix:!macx:SOURCES  += $$PWD/src/widgets/x11/qxtglobalshortcut_x11.cpp
macx:SOURCES        += $$PWD/src/widgets/mac/qxtglobalshortcut_mac.cpp
win32:SOURCES       += $$PWD/src/widgets/win/qxtglobalshortcut_win.cpp

unix:!macx:QT += x11extras
macx:QMAKE_LFLAGS += -framework Carbon -framework CoreFoundation
win32:LIBS += -luser32
