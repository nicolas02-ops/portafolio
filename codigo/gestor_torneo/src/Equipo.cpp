#include "Equipo.h"
#include <cstdio>
#include <cstdlib>

Equipo::Equipo()
    : pais(nullptr),
      confederacion(nullptr),
      rankingFIFA(999),
      plantilla(nullptr),
      cantidadJugadores(0),
      puntosGrupo(0),
      golesFavorGrupo(0),
      golesContraGrupo(0),
      golesFavorHistoricos(0),
      golesContraHistoricos(0),
      partidosGanadosHistoricos(0),
      partidosEmpatadosHistoricos(0),
      partidosPerdidosHistoricos(0),
      tarjetasAmarillasHistoricas(0),
      tarjetasRojasHistoricas(0),
      faltasHistoricas(0) {}

Equipo::Equipo(const Equipo& otro)
    : pais(nullptr), confederacion(nullptr), rankingFIFA(999), plantilla(nullptr), cantidadJugadores(0) {
    copiarDesde(otro);
}

Equipo& Equipo::operator=(const Equipo& otro) {
    if (this != &otro) {
        liberarPlantilla();
        liberarCadena(pais);
        liberarCadena(confederacion);
        copiarDesde(otro);
    }
    return *this;
}

Equipo::~Equipo() {
    liberarPlantilla();
    liberarCadena(pais);
    liberarCadena(confederacion);
}

void Equipo::liberarCadena(char*& texto) {
    if (texto != nullptr) {
        delete[] texto;
        texto = nullptr;
    }
}

void Equipo::liberarPlantilla() {
    if (plantilla != nullptr) {
        for (int i = 0; i < cantidadJugadores; ++i) {
            delete plantilla[i];
        }
        delete[] plantilla;
        plantilla = nullptr;
    }
    cantidadJugadores = 0;
}

void Equipo::copiarCadena(char*& destino, const char* origen) {
    int tam = 0;
    while (origen[tam] != '\0') {
        ++tam;
    }
    destino = new char[tam + 1];
    for (int i = 0; i < tam; ++i) {
        destino[i] = origen[i];
    }
    destino[tam] = '\0';
}

void Equipo::copiarDesde(const Equipo& otro) {
    copiarCadena(pais, otro.pais != nullptr ? otro.pais : "");
    copiarCadena(confederacion, otro.confederacion != nullptr ? otro.confederacion : "");
    rankingFIFA = otro.rankingFIFA;
    cantidadJugadores = otro.cantidadJugadores;
    puntosGrupo = otro.puntosGrupo;
    golesFavorGrupo = otro.golesFavorGrupo;
    golesContraGrupo = otro.golesContraGrupo;
    golesFavorHistoricos = otro.golesFavorHistoricos;
    golesContraHistoricos = otro.golesContraHistoricos;
    partidosGanadosHistoricos = otro.partidosGanadosHistoricos;
    partidosEmpatadosHistoricos = otro.partidosEmpatadosHistoricos;
    partidosPerdidosHistoricos = otro.partidosPerdidosHistoricos;
    tarjetasAmarillasHistoricas = otro.tarjetasAmarillasHistoricas;
    tarjetasRojasHistoricas = otro.tarjetasRojasHistoricas;
    faltasHistoricas = otro.faltasHistoricas;

    if (cantidadJugadores > 0) {
        plantilla = new Jugador*[cantidadJugadores];
        for (int i = 0; i < cantidadJugadores; ++i) {
            plantilla[i] = new Jugador(*(otro.plantilla[i]));
        }
    } else {
        plantilla = nullptr;
    }
}

void Equipo::configurar(const char* paisEquipo,
                        const char* confederacionEquipo,
                        int rankingEquipo,
                        int gfHistoricos,
                        int gcHistoricos,
                        int ganados,
                        int empatados,
                        int perdidos) {
    liberarPlantilla();
    liberarCadena(pais);
    liberarCadena(confederacion);

    copiarCadena(pais, paisEquipo != nullptr ? paisEquipo : "");
    copiarCadena(confederacion, confederacionEquipo != nullptr ? confederacionEquipo : "");
    rankingFIFA = rankingEquipo;
    golesFavorHistoricos = gfHistoricos;
    golesContraHistoricos = gcHistoricos;
    partidosGanadosHistoricos = ganados;
    partidosEmpatadosHistoricos = empatados;
    partidosPerdidosHistoricos = perdidos;
    tarjetasAmarillasHistoricas = 0;
    tarjetasRojasHistoricas = 0;
    faltasHistoricas = 0;
    resetDatosGrupo();
}

void Equipo::crearPlantillaArtificial(int cantidad) {
    liberarPlantilla();
    cantidadJugadores = cantidad;
    plantilla = new Jugador*[cantidadJugadores];

    int baseGoles = (cantidad > 0) ? (golesFavorHistoricos / cantidad) : 0;
    int sobrantes = (cantidad > 0) ? (golesFavorHistoricos % cantidad) : 0;

    for (int i = 0; i < cantidadJugadores; ++i) {
        plantilla[i] = new Jugador();
        int golesIniciales = baseGoles + (i < sobrantes ? 1 : 0);
        char nombreJugador[20];
        char apellidoJugador[20];
        std::snprintf(nombreJugador, sizeof(nombreJugador), "nombre%d", i + 1);
        std::snprintf(apellidoJugador, sizeof(apellidoJugador), "apellido%d", i + 1);
        plantilla[i]->configurar(nombreJugador, apellidoJugador, i + 1, golesIniciales);
    }
}

void Equipo::registrarResultadoGrupo(int golesFavor, int golesContra) {
    golesFavorGrupo += golesFavor;
    golesContraGrupo += golesContra;
    if (golesFavor > golesContra) {
        puntosGrupo += 3;
    } else if (golesFavor == golesContra) {
        ++puntosGrupo;
    }
}

void Equipo::registrarResultadoHistorico(int golesFavor, int golesContra) {
    golesFavorHistoricos += golesFavor;
    golesContraHistoricos += golesContra;

    if (golesFavor > golesContra) {
        ++partidosGanadosHistoricos;
    } else if (golesFavor == golesContra) {
        ++partidosEmpatadosHistoricos;
    } else {
        ++partidosPerdidosHistoricos;
    }
}

void Equipo::registrarDisciplinaHistorica(int amarillas, int rojas, int faltasCometidas) {
    tarjetasAmarillasHistoricas += amarillas;
    tarjetasRojasHistoricas += rojas;
    faltasHistoricas += faltasCometidas;
}

void Equipo::resetDatosGrupo() {
    puntosGrupo = 0;
    golesFavorGrupo = 0;
    golesContraGrupo = 0;
}

const char* Equipo::getPais() const { return (pais != nullptr) ? pais : ""; }

const char* Equipo::getConfederacion() const { return (confederacion != nullptr) ? confederacion : ""; }

int Equipo::getRankingFIFA() const { return rankingFIFA; }

int Equipo::getPuntosGrupo() const { return puntosGrupo; }

int Equipo::getDiferenciaGoles() const { return golesFavorGrupo - golesContraGrupo; }

int Equipo::getGolesFavor() const { return golesFavorGrupo; }

int Equipo::getGolesContraGrupo() const { return golesContraGrupo; }

int Equipo::getGolesFavorHistoricos() const { return golesFavorHistoricos; }

int Equipo::getGolesContraHistoricos() const { return golesContraHistoricos; }

int Equipo::getPartidosHistoricos() const {
    return partidosGanadosHistoricos + partidosEmpatadosHistoricos + partidosPerdidosHistoricos;
}

double Equipo::getPromedioGolesFavor() const {
    int partidos = getPartidosHistoricos();
    return (partidos > 0) ? static_cast<double>(golesFavorHistoricos) / partidos : 1.0;
}

double Equipo::getPromedioGolesContra() const {
    int partidos = getPartidosHistoricos();
    return (partidos > 0) ? static_cast<double>(golesContraHistoricos) / partidos : 1.0;
}

int Equipo::getCantidadJugadores() const { return cantidadJugadores; }

Jugador* Equipo::getJugador(int idx) const {
    if (idx < 0 || idx >= cantidadJugadores) {
        return nullptr;
    }
    return plantilla[idx];
}

bool Equipo::operator>(const Equipo& otro) const {
    if (getPuntosGrupo() != otro.getPuntosGrupo()) {
        return getPuntosGrupo() > otro.getPuntosGrupo();
    }
    if (getDiferenciaGoles() != otro.getDiferenciaGoles()) {
        return getDiferenciaGoles() > otro.getDiferenciaGoles();
    }
    if (getGolesFavor() != otro.getGolesFavor()) {
        return getGolesFavor() > otro.getGolesFavor();
    }
    return (std::rand() % 2) == 0;
}

std::ostream& operator<<(std::ostream& os, const Equipo& e) {
    os << e.getPais() << " [" << e.getConfederacion() << "]"
       << " (ranking FIFA: " << e.rankingFIFA << ")";
    return os;
}
