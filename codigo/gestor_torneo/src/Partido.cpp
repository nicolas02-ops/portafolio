#include "Partido.h"
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

Partido::Partido()
    : fecha(),
      equipo1(nullptr),
      equipo2(nullptr),
      convocados1(nullptr),
      convocados2(nullptr),
      goles1(0),
      goles2(0),
      posesion1(50.0),
      posesion2(50.0),
      huboProrroga(false) {
    std::strcpy(sede, "nombreSede");
    std::strcpy(hora, "00:00");
    std::strcpy(arbitros[0], "codArbitro1");
    std::strcpy(arbitros[1], "codArbitro2");
    std::strcpy(arbitros[2], "codArbitro3");
}

Partido::~Partido() {
    liberarConvocados();
}

void Partido::liberarConvocados() {
    if (convocados1 != nullptr) {
        delete[] convocados1;
        convocados1 = nullptr;
    }
    if (convocados2 != nullptr) {
        delete[] convocados2;
        convocados2 = nullptr;
    }
}

double Partido::generarAleatorio01() const {
    return static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
}

void Partido::configurar(const Fecha& fechaPartido, Equipo* primerEquipo, Equipo* segundoEquipo) {
    liberarConvocados();
    fecha = fechaPartido;
    equipo1 = primerEquipo;
    equipo2 = segundoEquipo;
    std::strcpy(sede, "nombreSede");
    std::strcpy(hora, "00:00");
    std::strcpy(arbitros[0], "codArbitro1");
    std::strcpy(arbitros[1], "codArbitro2");
    std::strcpy(arbitros[2], "codArbitro3");
    goles1 = 0;
    goles2 = 0;
    posesion1 = 50.0;
    posesion2 = 50.0;
    huboProrroga = false;
}

void Partido::prepararConvocados(Equipo* equipo, RegistroJugadorPartido*& convocados) {
    int total = equipo->getCantidadJugadores();
    int cantidadConvocados = 11;
    convocados = new RegistroJugadorPartido[cantidadConvocados];
    bool* usados = new bool[total];

    for (int i = 0; i < total; ++i) {
        usados[i] = false;
    }

    for (int i = 0; i < cantidadConvocados; ++i) {
        int indice = std::rand() % total;
        while (usados[indice]) {
            indice = std::rand() % total;
        }
        usados[indice] = true;
        convocados[i].configurar(equipo->getJugador(indice));
    }

    delete[] usados;
}

int Partido::calcularGolesEsperados(Equipo* atacante, Equipo* defensor) const {
    const double alpha = 0.6;
    const double beta = 0.4;
    const double mu = 1.35;

    double lambda = mu * (alpha * atacante->getPromedioGolesFavor() + beta * defensor->getPromedioGolesContra());
    if (lambda < 0.3) {
        lambda = 0.3;
    }

    int base = static_cast<int>(lambda);
    double fraccion = lambda - base;
    if (generarAleatorio01() < fraccion) {
        ++base;
    }
    if (base > 6) {
        base = 6;
    }
    return base;
}

void Partido::asignarEventosEquipo(RegistroJugadorPartido* convocados, int golesEquipo, int minutosPorJugador) {
    const int cantidadConvocados = 11;

    for (int i = 0; i < cantidadConvocados; ++i) {
        convocados[i].setMinutosJugados(minutosPorJugador);

        if (generarAleatorio01() < 0.13) {
            convocados[i].registrarFalta();
            if (generarAleatorio01() < 0.0275) {
                convocados[i].registrarFalta();
                if (generarAleatorio01() < 0.007) {
                    convocados[i].registrarFalta();
                }
            }
        }

        if (generarAleatorio01() < 0.06) {
            convocados[i].registrarAmarilla();
            if (generarAleatorio01() < 0.0115) {
                convocados[i].registrarAmarilla();
                convocados[i].registrarRoja();
            }
        }
    }

    int golesAsignados = 0;
    for (int vuelta = 0; vuelta < 3 && golesAsignados < golesEquipo; ++vuelta) {
        for (int i = 0; i < cantidadConvocados && golesAsignados < golesEquipo; ++i) {
            if (generarAleatorio01() < 0.04) {
                convocados[i].registrarGol();
                ++golesAsignados;
            }
        }
    }

    while (golesAsignados < golesEquipo) {
        int indice = std::rand() % cantidadConvocados;
        convocados[indice].registrarGol();
        ++golesAsignados;
    }
}

void Partido::actualizarHistoricos(bool faseDeGrupos) {
    int amarillas1 = 0, rojas1 = 0, faltas1 = 0;
    int amarillas2 = 0, rojas2 = 0, faltas2 = 0;

    for (int i = 0; i < 11; ++i) {
        amarillas1 += convocados1[i].getAmarillas();
        rojas1 += convocados1[i].getRojas();
        faltas1 += convocados1[i].getFaltas();
        convocados1[i].aplicarAHistoricos();

        amarillas2 += convocados2[i].getAmarillas();
        rojas2 += convocados2[i].getRojas();
        faltas2 += convocados2[i].getFaltas();
        convocados2[i].aplicarAHistoricos();
    }

    equipo1->registrarResultadoHistorico(goles1, goles2);
    equipo2->registrarResultadoHistorico(goles2, goles1);
    equipo1->registrarDisciplinaHistorica(amarillas1, rojas1, faltas1);
    equipo2->registrarDisciplinaHistorica(amarillas2, rojas2, faltas2);

    if (faseDeGrupos) {
        equipo1->registrarResultadoGrupo(goles1, goles2);
        equipo2->registrarResultadoGrupo(goles2, goles1);
    }
}

void Partido::simular(bool eliminacionDirecta, bool faseDeGrupos) {
    if (equipo1 == nullptr || equipo2 == nullptr) {
        return;
    }

    prepararConvocados(equipo1, convocados1);
    prepararConvocados(equipo2, convocados2);

    goles1 = calcularGolesEsperados(equipo1, equipo2);
    goles2 = calcularGolesEsperados(equipo2, equipo1);

    double fuerza1 = 1.0 / equipo1->getRankingFIFA();
    double fuerza2 = 1.0 / equipo2->getRankingFIFA();
    posesion1 = (fuerza1 / (fuerza1 + fuerza2)) * 100.0;
    posesion2 = 100.0 - posesion1;

    int minutos = 90;
    if (eliminacionDirecta && goles1 == goles2) {
        huboProrroga = true;
        minutos = 120;
        double probEquipo1 = static_cast<double>(equipo2->getRankingFIFA()) /
                             static_cast<double>(equipo1->getRankingFIFA() + equipo2->getRankingFIFA());
        if (generarAleatorio01() < probEquipo1) {
            ++goles1;
        } else {
            ++goles2;
        }
    }

    asignarEventosEquipo(convocados1, goles1, minutos);
    asignarEventosEquipo(convocados2, goles2, minutos);
    actualizarHistoricos(faseDeGrupos);
}

int Partido::getGolesEquipo1() const { return goles1; }

int Partido::getGolesEquipo2() const { return goles2; }

Equipo* Partido::getEquipo1() const { return equipo1; }

Equipo* Partido::getEquipo2() const { return equipo2; }

Equipo* Partido::getGanador() const {
    return (goles1 > goles2) ? equipo1 : equipo2;
}

Equipo* Partido::getPerdedor() const {
    return (goles1 > goles2) ? equipo2 : equipo1;
}

const Fecha& Partido::getFecha() const { return fecha; }

bool Partido::getHuboProrroga() const { return huboProrroga; }

void Partido::imprimirResumen() const {
    cout << fecha << " " << hora
         << " | Sede: " << sede
         << " | Arbitros: " << arbitros[0] << ", " << arbitros[1] << ", " << arbitros[2]
         << " | " << equipo1->getPais() << " " << goles1 << " - " << goles2
         << " " << equipo2->getPais()
         << " | Posesion: " << std::fixed << std::setprecision(1)
         << posesion1 << "% - " << posesion2 << "%";
    if (huboProrroga) {
        cout << " | Prorroga";
    }
    cout << "\n";
}

void Partido::imprimirGoleadores() const {
    cout << "  Goleadores " << equipo1->getPais() << ": ";
    bool alguno = false;
    for (int i = 0; i < 11; ++i) {
        for (int g = 0; g < convocados1[i].getGoles(); ++g) {
            cout << convocados1[i].getJugador()->getNumeroCamiseta() << " ";
            alguno = true;
        }
    }
    if (!alguno) {
        cout << "sin goles";
    }
    cout << "\n";

    cout << "  Goleadores " << equipo2->getPais() << ": ";
    alguno = false;
    for (int i = 0; i < 11; ++i) {
        for (int g = 0; g < convocados2[i].getGoles(); ++g) {
            cout << convocados2[i].getJugador()->getNumeroCamiseta() << " ";
            alguno = true;
        }
    }
    if (!alguno) {
        cout << "sin goles";
    }
    cout << "\n";
}
