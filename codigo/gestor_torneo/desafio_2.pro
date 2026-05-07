QT -= gui

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++17

INCLUDEPATH += include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Equipo.cpp \
    src/EstadisticaHistorica.cpp \
    src/EstadisticaPartido.cpp \
    src/Fecha.cpp \
    src/Grupo.cpp \
    src/Jugador.cpp \
    src/MonitorRecursos.cpp \
    src/Partido.cpp \
    src/RegistroJugadorPartido.cpp \
    src/Torneo.cpp \
    src/main.cpp

HEADERS += \
    include/Equipo.h \
    include/EstadisticaHistorica.h \
    include/EstadisticaPartido.h \
    include/Fecha.h \
    include/Grupo.h \
    include/Jugador.h \
    include/MonitorRecursos.h \
    include/Partido.h \
    include/RegistroJugadorPartido.h \
    include/Torneo.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
