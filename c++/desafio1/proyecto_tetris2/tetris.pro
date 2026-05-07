QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
    src/main.cpp \
    src/board.cpp \
    src/pieces.cpp \
    src/game.cpp

HEADERS += \
    src/board.h \
    src/pieces.h \
    src/game.h

DEFINES += QT_NO_STRING