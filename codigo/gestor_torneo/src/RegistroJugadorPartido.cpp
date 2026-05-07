#include "RegistroJugadorPartido.h"

RegistroJugadorPartido::RegistroJugadorPartido()
    : jugador(nullptr), asistencias(0), estadistica() {}

void RegistroJugadorPartido::configurar(Jugador* jugadorPartido) {
    jugador = jugadorPartido;
    asistencias = 0;
    estadistica.reset();
}

void RegistroJugadorPartido::registrarGol() { estadistica.registrarGol(); }

void RegistroJugadorPartido::registrarAmarilla() { estadistica.registrarAmarilla(); }

void RegistroJugadorPartido::registrarRoja() { estadistica.registrarRoja(); }

void RegistroJugadorPartido::registrarFalta() { estadistica.registrarFalta(); }

void RegistroJugadorPartido::registrarAsistencia() { ++asistencias; }

void RegistroJugadorPartido::setMinutosJugados(int minutos) { estadistica.setMinutosJugados(minutos); }

void RegistroJugadorPartido::aplicarAHistoricos() {
    if (jugador == nullptr) {
        return;
    }

    jugador->sumarPartido();
    jugador->sumarMinutos(estadistica.getMinutosJugados());

    for (int i = 0; i < estadistica.getGoles(); ++i) {
        jugador->sumarGol();
    }
    for (int i = 0; i < estadistica.getTarjetasAmarillas(); ++i) {
        jugador->sumarAmarilla();
    }
    for (int i = 0; i < estadistica.getTarjetasRojas(); ++i) {
        jugador->sumarRoja();
    }
    for (int i = 0; i < estadistica.getFaltas(); ++i) {
        jugador->sumarFalta();
    }
    for (int i = 0; i < asistencias; ++i) {
        jugador->sumarAsistencia();
    }
}

Jugador* RegistroJugadorPartido::getJugador() const { return jugador; }

int RegistroJugadorPartido::getGoles() const { return estadistica.getGoles(); }

int RegistroJugadorPartido::getAmarillas() const { return estadistica.getTarjetasAmarillas(); }

int RegistroJugadorPartido::getRojas() const { return estadistica.getTarjetasRojas(); }

int RegistroJugadorPartido::getFaltas() const { return estadistica.getFaltas(); }

int RegistroJugadorPartido::getMinutosJugados() const { return estadistica.getMinutosJugados(); }

int RegistroJugadorPartido::getAsistencias() const { return asistencias; }
