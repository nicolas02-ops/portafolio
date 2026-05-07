#include "EstadisticaHistorica.h"

EstadisticaHistorica::EstadisticaHistorica()
    : mundialesGanados(0),
      promedioGoles(0.0f),
      golesFavor(0),
      golesContra(0),
      partidosGanados(0),
      partidosEmpatados(0),
      partidosPerdidos(0),
      puntosGrupo(0) {}

void EstadisticaHistorica::actualizarDatos(int golesAFavor, int golesEnContra) {
    golesFavor += golesAFavor;
    golesContra += golesEnContra;

    if (golesAFavor > golesEnContra) {
        ++partidosGanados;
        puntosGrupo += 3;
    } else if (golesAFavor == golesEnContra) {
        ++partidosEmpatados;
        puntosGrupo += 1;
    } else {
        ++partidosPerdidos;
    }

    int partidosTotales = partidosGanados + partidosEmpatados + partidosPerdidos;
    if (partidosTotales > 0) {
        promedioGoles = static_cast<float>(golesFavor) / static_cast<float>(partidosTotales);
    }
}

void EstadisticaHistorica::resetGrupo() {
    puntosGrupo = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
}

int EstadisticaHistorica::getPuntosGrupo() const { return puntosGrupo; }

int EstadisticaHistorica::getDiferenciaGoles() const { return golesFavor - golesContra; }

int EstadisticaHistorica::getGolesFavor() const { return golesFavor; }

float EstadisticaHistorica::getPromedioGoles() const { return promedioGoles; }
