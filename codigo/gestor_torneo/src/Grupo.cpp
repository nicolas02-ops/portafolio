#include "Grupo.h"
#include <cstring>
#include <iostream>

using namespace std;

Grupo::Grupo() : letra('?'), equipos(new Equipo*[4]), cantidadEquipos(0) {
    for (int i = 0; i < 4; ++i) {
        equipos[i] = nullptr;
    }
}

Grupo::~Grupo() {
    delete[] equipos;
}

void Grupo::setLetra(char idGrupo) { letra = idGrupo; }

char Grupo::getLetra() const { return letra; }

bool Grupo::puedeAgregarEquipo(Equipo* equipo) const {
    if (equipo == nullptr || cantidadEquipos >= 4) {
        return false;
    }

    int coincidenciasMismaConf = 0;
    for (int i = 0; i < cantidadEquipos; ++i) {
        if (std::strcmp(equipos[i]->getConfederacion(), equipo->getConfederacion()) == 0) {
            ++coincidenciasMismaConf;
        }
    }

    if (std::strcmp(equipo->getConfederacion(), "UEFA") == 0) {
        return coincidenciasMismaConf < 2;
    }
    return coincidenciasMismaConf == 0;
}

void Grupo::agregarEquipo(Equipo* equipo) {
    if (puedeAgregarEquipo(equipo)) {
        equipos[cantidadEquipos] = equipo;
        ++cantidadEquipos;
    }
}

void Grupo::agregarEquipoForzado(Equipo* equipo) {
    if (equipo != nullptr && cantidadEquipos < 4) {
        equipos[cantidadEquipos] = equipo;
        ++cantidadEquipos;
    }
}

void Grupo::quitarUltimoEquipo() {
    if (cantidadEquipos > 0) {
        --cantidadEquipos;
        equipos[cantidadEquipos] = nullptr;
    }
}

void Grupo::intercambiarEquipos(int a, int b) {
    Equipo* temporal = equipos[a];
    equipos[a] = equipos[b];
    equipos[b] = temporal;
}

void Grupo::ordenarTabla() {
    for (int i = 0; i < cantidadEquipos - 1; ++i) {
        for (int j = 0; j < cantidadEquipos - i - 1; ++j) {
            if (!((*equipos[j]) > (*equipos[j + 1]))) {
                intercambiarEquipos(j, j + 1);
            }
        }
    }
}

Equipo* Grupo::getEquipo(int idx) const {
    if (idx < 0 || idx >= cantidadEquipos) {
        return nullptr;
    }
    return equipos[idx];
}

int Grupo::getCantidadEquipos() const { return cantidadEquipos; }

void Grupo::imprimirTabla() const {
    cout << "Tabla grupo " << letra << ":\n";
    for (int i = 0; i < cantidadEquipos; ++i) {
        cout << "  " << (i + 1) << ". " << equipos[i]->getPais()
             << " | Pts: " << equipos[i]->getPuntosGrupo()
             << " | DG: " << equipos[i]->getDiferenciaGoles()
             << " | GF: " << equipos[i]->getGolesFavor() << "\n";
    }
}
