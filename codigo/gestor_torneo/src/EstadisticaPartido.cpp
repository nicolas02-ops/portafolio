#include "EstadisticaPartido.h"

EstadisticaPartido::EstadisticaPartido()
    : goles(0), tarjetasAmarillas(0), tarjetasRojas(0), faltas(0), minutosJugados(0) {}

void EstadisticaPartido::reset() {
    goles = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    minutosJugados = 0;
}

void EstadisticaPartido::registrarGol() { ++goles; }

void EstadisticaPartido::registrarAmarilla() { ++tarjetasAmarillas; }

void EstadisticaPartido::registrarRoja() { ++tarjetasRojas; }

void EstadisticaPartido::registrarFalta() { ++faltas; }

void EstadisticaPartido::setMinutosJugados(int minutos) { minutosJugados = minutos; }

int EstadisticaPartido::getGoles() const { return goles; }

int EstadisticaPartido::getTarjetasAmarillas() const { return tarjetasAmarillas; }

int EstadisticaPartido::getTarjetasRojas() const { return tarjetasRojas; }

int EstadisticaPartido::getFaltas() const { return faltas; }

int EstadisticaPartido::getMinutosJugados() const { return minutosJugados; }
