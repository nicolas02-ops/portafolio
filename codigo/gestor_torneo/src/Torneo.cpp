#include "Torneo.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

namespace {
const char* ARCHIVO_EQUIPOS = "txt/selecciones_clasificadas_mundial.csv";
const char* ARCHIVO_EQUIPOS_ALT = "../../txt/selecciones_clasificadas_mundial.csv";
const char* ARCHIVO_JUGADORES = "txt/jugadores_actualizados.csv";
const char* ARCHIVO_JUGADORES_ALT = "../../txt/jugadores_actualizados.csv";
const char* DATOS_EQUIPOS_BASE[48] = {
    "Estados Unidos,CONCACAF,16,95,62,32,10,12",
    "Mexico,CONCACAF,8,98,70,30,11,13",
    "Canada,CONCACAF,19,70,68,18,9,13",
    "Argentina,CONMEBOL,1,152,71,51,15,16",
    "Brasil,CONMEBOL,2,143,66,48,18,15",
    "Uruguay,CONMEBOL,13,117,75,36,14,16",
    "Colombia,CONMEBOL,11,109,79,31,14,17",
    "Chile,CONMEBOL,35,86,92,24,10,20",
    "Ecuador,CONMEBOL,20,91,84,26,13,18",
    "Peru,CONMEBOL,47,79,95,22,11,22",
    "Paraguay,CONMEBOL,34,74,89,20,12,21",
    "Bolivia,CONMEBOL,48,60,120,11,10,32",
    "Francia,UEFA,2,149,68,49,17,14",
    "Espana,UEFA,3,141,73,46,16,15",
    "Inglaterra,UEFA,4,138,70,45,18,12",
    "Alemania,UEFA,14,130,77,40,14,18",
    "Italia,UEFA,15,126,69,39,17,15",
    "Portugal,UEFA,7,129,71,42,19,14",
    "Paises Bajos,UEFA,16,127,72,38,18,13",
    "Belgica,UEFA,12,131,78,41,17,14",
    "Croacia,UEFA,25,112,74,34,15,16",
    "Serbia,UEFA,26,89,83,24,12,19",
    "Suiza,UEFA,22,101,72,28,16,18",
    "Dinamarca,UEFA,21,97,74,27,15,17",
    "Marruecos,CAF,17,104,73,30,13,14",
    "Senegal,CAF,9,96,76,29,12,16",
    "Nigeria,CAF,24,90,80,25,13,17",
    "Egipto,CAF,36,84,79,24,11,18",
    "Japon,AFC,18,97,69,31,10,15",
    "Corea del Sur,AFC,28,92,75,28,11,17",
    "Australia,AFC,29,88,73,27,10,18",
    "Iran,AFC,10,94,66,30,9,16",
    "Arabia Saudita,AFC,46,76,88,19,10,21",
    "Qatar,AFC,45,73,86,18,9,23",
    "Costa Rica,CONCACAF,31,78,87,20,11,20",
    "Panama,CONCACAF,30,80,82,22,12,19",
    "Honduras,CONCACAF,44,67,94,16,10,24",
    "Jamaica,CONCACAF,43,69,90,17,11,22",
    "Venezuela,CONMEBOL,33,77,86,21,10,21",
    "Turquia,UEFA,32,93,85,25,12,18",
    "Grecia,UEFA,37,78,84,21,10,19",
    "Polonia,UEFA,27,99,88,27,11,19",
    "Austria,UEFA,23,95,77,28,13,16",
    "Ucrania,UEFA,38,90,78,26,12,17",
    "Suecia,UEFA,39,88,81,24,14,16",
    "Noruega,UEFA,40,83,80,23,11,19",
    "Irlanda,UEFA,41,71,85,18,12,22",
    "Rumania,UEFA,42,79,83,20,13,19"
};

void partirCSV(const char* linea, char campos[][64], int cantidadEsperada) {
    for (int i = 0; i < cantidadEsperada; ++i) {
        campos[i][0] = '\0';
    }

    int inicio = 0;
    int indice = 0;
    int longitud = static_cast<int>(std::strlen(linea));
    for (int i = 0; i <= longitud && indice < cantidadEsperada; ++i) {
        if (i == longitud || linea[i] == ',') {
            int cantidadCopiar = i - inicio;
            if (cantidadCopiar > 63) {
                cantidadCopiar = 63;
            }
            std::strncpy(campos[indice], linea + inicio, cantidadCopiar);
            campos[indice][cantidadCopiar] = '\0';
            ++indice;
            inicio = i + 1;
        }
    }
}

const char* resolverRutaExistente(const char* primaria, const char* alternativa) {
    std::ifstream prueba(primaria);
    if (prueba.good()) {
        return primaria;
    }
    prueba.close();
    return alternativa;
}

bool cargarEquipoDesdeLinea(Equipo* equipo, const char* linea) {
    char campos[8][64];
    partirCSV(linea, campos, 8);

    for (int i = 0; i < 8; ++i) {
        if (campos[i][0] == '\0') {
            return false;
        }
    }

    equipo->configurar(campos[0],
                       campos[1],
                       std::atoi(campos[2]),
                       std::atoi(campos[3]),
                       std::atoi(campos[4]),
                       std::atoi(campos[5]),
                       std::atoi(campos[6]),
                       std::atoi(campos[7]));
    equipo->crearPlantillaArtificial(26);
    return true;
}

const char* resolverRutaEscritura(const char* primaria, const char* alternativa) {
    std::ofstream prueba(primaria, std::ios::app);
    if (prueba.good()) {
        prueba.close();
        return primaria;
    }
    prueba.close();
    return alternativa;
}

bool asignarBomboConBacktracking(Grupo** grupos, Equipo** bombo, bool* usado, int asignados, int equiposPreviosPorGrupo) {
    if (asignados == 12) {
        return true;
    }

    int siguienteGrupo = -1;
    int menorCantidadOpciones = 13;
    int opcionesPorGrupo[12][12];
    int cantidadOpcionesGrupo[12];

    for (int g = 0; g < 12; ++g) {
        cantidadOpcionesGrupo[g] = 0;
        if (grupos[g]->getCantidadEquipos() != equiposPreviosPorGrupo) {
            continue;
        }

        for (int i = 0; i < 12; ++i) {
            if (!usado[i] && grupos[g]->puedeAgregarEquipo(bombo[i])) {
                opcionesPorGrupo[g][cantidadOpcionesGrupo[g]++] = i;
            }
        }

        if (cantidadOpcionesGrupo[g] == 0) {
            return false;
        }

        if (cantidadOpcionesGrupo[g] < menorCantidadOpciones) {
            menorCantidadOpciones = cantidadOpcionesGrupo[g];
            siguienteGrupo = g;
        }
    }

    if (siguienteGrupo == -1) {
        return false;
    }

    for (int i = cantidadOpcionesGrupo[siguienteGrupo] - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = opcionesPorGrupo[siguienteGrupo][i];
        opcionesPorGrupo[siguienteGrupo][i] = opcionesPorGrupo[siguienteGrupo][j];
        opcionesPorGrupo[siguienteGrupo][j] = tmp;
    }

    for (int i = 0; i < cantidadOpcionesGrupo[siguienteGrupo]; ++i) {
        int elegido = opcionesPorGrupo[siguienteGrupo][i];
        grupos[siguienteGrupo]->agregarEquipo(bombo[elegido]);
        usado[elegido] = true;

        if (asignarBomboConBacktracking(grupos, bombo, usado, asignados + 1, equiposPreviosPorGrupo)) {
            return true;
        }

        usado[elegido] = false;
        grupos[siguienteGrupo]->quitarUltimoEquipo();
    }

    return false;
}

bool gruposCumplenRestricciones(Grupo** grupos) {
    for (int g = 0; g < 12; ++g) {
        int uefa = 0;
        int conmebol = 0;
        int concacaf = 0;
        int caf = 0;
        int afc = 0;

        for (int i = 0; i < grupos[g]->getCantidadEquipos(); ++i) {
            const char* conf = grupos[g]->getEquipo(i)->getConfederacion();
            if (std::strcmp(conf, "UEFA") == 0) {
                ++uefa;
            } else if (std::strcmp(conf, "CONMEBOL") == 0) {
                ++conmebol;
            } else if (std::strcmp(conf, "CONCACAF") == 0) {
                ++concacaf;
            } else if (std::strcmp(conf, "CAF") == 0) {
                ++caf;
            } else if (std::strcmp(conf, "AFC") == 0) {
                ++afc;
            }
        }

        if (uefa > 2 || conmebol > 1 || concacaf > 1 || caf > 1 || afc > 1) {
            return false;
        }
    }
    return true;
}

bool asignarBombosGlobalmente(Grupo** grupos, Equipo** bombosLineales, bool usados[48], int indiceBombo, int asignadosEnBombo) {
    if (indiceBombo == 4) {
        return gruposCumplenRestricciones(grupos);
    }

    if (asignadosEnBombo == 12) {
        return asignarBombosGlobalmente(grupos, bombosLineales, usados, indiceBombo + 1, 0);
    }

    int siguienteGrupo = -1;
    int menorCantidadOpciones = 13;
    int opcionesPorGrupo[12][12];
    int cantidadOpcionesGrupo[12];

    for (int g = 0; g < 12; ++g) {
        cantidadOpcionesGrupo[g] = 0;
        if (grupos[g]->getCantidadEquipos() != indiceBombo) {
            continue;
        }

        for (int i = 0; i < 12; ++i) {
            int indiceEquipoBombo = indiceBombo * 12 + i;
            if (!usados[indiceEquipoBombo] && grupos[g]->puedeAgregarEquipo(bombosLineales[indiceEquipoBombo])) {
                opcionesPorGrupo[g][cantidadOpcionesGrupo[g]++] = indiceEquipoBombo;
            }
        }

        if (cantidadOpcionesGrupo[g] == 0) {
            return false;
        }

        if (cantidadOpcionesGrupo[g] < menorCantidadOpciones) {
            menorCantidadOpciones = cantidadOpcionesGrupo[g];
            siguienteGrupo = g;
        }
    }

    if (siguienteGrupo == -1) {
        return false;
    }

    for (int i = cantidadOpcionesGrupo[siguienteGrupo] - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int temporal = opcionesPorGrupo[siguienteGrupo][i];
        opcionesPorGrupo[siguienteGrupo][i] = opcionesPorGrupo[siguienteGrupo][j];
        opcionesPorGrupo[siguienteGrupo][j] = temporal;
    }

    for (int i = 0; i < cantidadOpcionesGrupo[siguienteGrupo]; ++i) {
        int indiceEquipoBombo = opcionesPorGrupo[siguienteGrupo][i];
        grupos[siguienteGrupo]->agregarEquipo(bombosLineales[indiceEquipoBombo]);
        usados[indiceEquipoBombo] = true;

        if (asignarBombosGlobalmente(grupos, bombosLineales, usados, indiceBombo, asignadosEnBombo + 1)) {
            return true;
        }

        usados[indiceEquipoBombo] = false;
        grupos[siguienteGrupo]->quitarUltimoEquipo();
    }

    return false;
}

bool asignarGruposPrecalculados(Grupo** grupos, Equipo** bombosLineales) {
    int asignacion[12][4] = {
        {0, 1, 3, 10},
        {1, 2, 5, 8},
        {2, 3, 6, 9},
        {11, 8, 11, 7},
        {10, 9, 7, 6},
        {7, 10, 2, 11},
        {3, 0, 4, 0},
        {4, 4, 8, 1},
        {5, 5, 9, 2},
        {6, 6, 10, 3},
        {8, 7, 0, 4},
        {9, 11, 1, 5}
    };

    for (int g = 0; g < 12; ++g) {
        for (int b = 0; b < 4; ++b) {
            Equipo* equipo = bombosLineales[b * 12 + asignacion[g][b]];
            if (!grupos[g]->puedeAgregarEquipo(equipo)) {
                return false;
            }
            grupos[g]->agregarEquipo(equipo);
        }
    }

    return gruposCumplenRestricciones(grupos);
}

bool agregarPrimerEquipoDisponible(Grupo* grupo, Equipo** equiposOrdenados, bool* usado, const char* confederacionBuscada) {
    for (int i = 0; i < 48; ++i) {
        if (usado[i]) {
            continue;
        }

        Equipo* equipo = equiposOrdenados[i];
        bool coincideConfederacion = (confederacionBuscada == nullptr) ||
                                     (std::strcmp(equipo->getConfederacion(), confederacionBuscada) == 0);

        if (coincideConfederacion && grupo->puedeAgregarEquipo(equipo)) {
            grupo->agregarEquipo(equipo);
            usado[i] = true;
            return true;
        }
    }
    return false;
}

bool asignarGruposPorConfederacion(Grupo** grupos, Equipo** equiposOrdenados) {
    bool usado[48];
    for (int i = 0; i < 48; ++i) {
        usado[i] = false;
    }

    const char* primerasConfederaciones[12] = {
        "CONMEBOL", "CONCACAF", "CAF", "AFC",
        "CONMEBOL", "CONCACAF", "CAF", "AFC",
        "CONMEBOL", "CONCACAF", "CAF", "AFC"
    };

    const char* segundasConfederaciones[12] = {
        "CONCACAF", "CONMEBOL", "AFC", "CAF",
        "AFC", "CAF", "CONCACAF", "CONMEBOL",
        "CAF", "AFC", "CONMEBOL", "CONCACAF"
    };

    for (int g = 0; g < 12; ++g) {
        agregarPrimerEquipoDisponible(grupos[g], equiposOrdenados, usado, primerasConfederaciones[g]);
        agregarPrimerEquipoDisponible(grupos[g], equiposOrdenados, usado, segundasConfederaciones[g]);
    }

    for (int g = 0; g < 12; ++g) {
        while (grupos[g]->getCantidadEquipos() < 4 && agregarPrimerEquipoDisponible(grupos[g], equiposOrdenados, usado, "UEFA")) {
        }
    }

    for (int g = 0; g < 12; ++g) {
        while (grupos[g]->getCantidadEquipos() < 4) {
            if (!agregarPrimerEquipoDisponible(grupos[g], equiposOrdenados, usado, nullptr)) {
                return false;
            }
        }
    }

    return gruposCumplenRestricciones(grupos);
}

void asignarGruposForzadosPorBombo(Grupo** grupos, Equipo** bombosLineales) {
    for (int b = 0; b < 4; ++b) {
        for (int g = 0; g < 12; ++g) {
            grupos[g]->agregarEquipoForzado(bombosLineales[b * 12 + g]);
        }
    }
}

}

Torneo::Torneo()
    : grupos(nullptr),
      equipos(nullptr),
      cantidadEquipos(48),
      monitor(),
      partidosGrupos(nullptr),
      partidosDieciseisavos(nullptr),
      partidosOctavos(nullptr),
      partidosCuartos(nullptr),
      partidosSemifinales(nullptr),
      partidoTercerPuesto(nullptr),
      partidoFinal(nullptr),
      datosCargados(false),
      gruposConformados(false),
      faseGruposSimulada(false),
      torneoFinalizado(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    grupos = new Grupo*[12];
    for (int i = 0; i < 12; ++i) {
        grupos[i] = new Grupo();
        grupos[i]->setLetra(static_cast<char>('A' + i));
    }

    equipos = new Equipo*[cantidadEquipos];
    for (int i = 0; i < cantidadEquipos; ++i) {
        equipos[i] = new Equipo();
    }
}

Torneo::~Torneo() {
    liberarPartidos(partidosGrupos, 72);
    liberarPartidos(partidosDieciseisavos, 16);
    liberarPartidos(partidosOctavos, 8);
    liberarPartidos(partidosCuartos, 4);
    liberarPartidos(partidosSemifinales, 2);
    delete partidoTercerPuesto;
    delete partidoFinal;

    if (grupos != nullptr) {
        for (int i = 0; i < 12; ++i) {
            delete grupos[i];
        }
        delete[] grupos;
    }

    if (equipos != nullptr) {
        for (int i = 0; i < cantidadEquipos; ++i) {
            delete equipos[i];
        }
        delete[] equipos;
    }
}

void Torneo::liberarPartidos(Partido**& lista, int cantidad) {
    if (lista == nullptr) {
        return;
    }
    for (int i = 0; i < cantidad; ++i) {
        delete lista[i];
    }
    delete[] lista;
    lista = nullptr;
}

void Torneo::crearArchivoBaseSiNoExiste() {
    const char* rutaEscritura = resolverRutaEscritura(ARCHIVO_EQUIPOS, ARCHIVO_EQUIPOS_ALT);
    std::ofstream archivo(rutaEscritura);
    archivo << "pais,confederacion,ranking,gf,gc,ganados,empatados,perdidos\n";
    for (int i = 0; i < 48; ++i) {
        archivo << DATOS_EQUIPOS_BASE[i] << "\n";
    }
}

void Torneo::cargarEquiposDesdeCSV() {
    crearArchivoBaseSiNoExiste();
    const char* rutaLectura = resolverRutaExistente(ARCHIVO_EQUIPOS, ARCHIVO_EQUIPOS_ALT);
    std::ifstream archivo(rutaLectura);
    char linea[256];
    archivo.getline(linea, sizeof(linea));

    int indice = 0;
    while (archivo.getline(linea, sizeof(linea)) && indice < cantidadEquipos) {
        if (cargarEquipoDesdeLinea(equipos[indice], linea)) {
            monitor.registrarIteracion(1);
            ++indice;
        }
    }

    if (indice < cantidadEquipos) {
        for (int i = indice; i < cantidadEquipos; ++i) {
            cargarEquipoDesdeLinea(equipos[i], DATOS_EQUIPOS_BASE[i]);
            monitor.registrarIteracion(1);
        }
        crearArchivoBaseSiNoExiste();
    }

    datosCargados = true;
    gruposConformados = false;
    faseGruposSimulada = false;
    torneoFinalizado = false;
}

void Torneo::cargarOActualizarDatos() {
    monitor.reset();
    cargarEquiposDesdeCSV();
    cout << "\nDatos historicos cargados correctamente.\n";
}

void Torneo::crearBombos(Equipo*** bombos) {
    Equipo** ordenados = new Equipo*[cantidadEquipos];
    for (int i = 0; i < cantidadEquipos; ++i) {
        ordenados[i] = equipos[i];
    }

    for (int i = 0; i < cantidadEquipos - 1; ++i) {
        for (int j = 0; j < cantidadEquipos - i - 1; ++j) {
            if (ordenados[j]->getRankingFIFA() > ordenados[j + 1]->getRankingFIFA()) {
                Equipo* tmp = ordenados[j];
                ordenados[j] = ordenados[j + 1];
                ordenados[j + 1] = tmp;
            }
            monitor.registrarIteracion(1);
        }
    }

    int posicionEEUU = -1;
    for (int i = 0; i < cantidadEquipos; ++i) {
        if (std::strcmp(ordenados[i]->getPais(), "Estados Unidos") == 0) {
            posicionEEUU = i;
            break;
        }
    }
    if (posicionEEUU > 0) {
        Equipo* anfitrion = ordenados[posicionEEUU];
        for (int i = posicionEEUU; i > 0; --i) {
            ordenados[i] = ordenados[i - 1];
        }
        ordenados[0] = anfitrion;
    }

    *bombos = new Equipo*[cantidadEquipos];
    for (int i = 0; i < cantidadEquipos; ++i) {
        (*bombos)[i] = ordenados[i];
    }

    delete[] ordenados;
}

void Torneo::limpiarGrupos() {
    liberarPartidos(partidosGrupos, 72);

    for (int i = 0; i < 12; ++i) {
        delete grupos[i];
        grupos[i] = new Grupo();
        grupos[i]->setLetra(static_cast<char>('A' + i));
    }
}

bool Torneo::asignarBomboAGrupos(Equipo** bombo) {
    bool* usado = new bool[12];
    for (int i = 0; i < 12; ++i) {
        usado[i] = false;
    }
    int equiposPreviosPorGrupo = grupos[0]->getCantidadEquipos();
    bool logrado = asignarBomboConBacktracking(grupos, bombo, usado, 0, equiposPreviosPorGrupo);
    delete[] usado;
    return logrado;
}

void Torneo::conformarGrupos() {
    if (!datosCargados) {
        cargarOActualizarDatos();
    }

    Equipo** bombosLineales = nullptr;
    crearBombos(&bombosLineales);

    limpiarGrupos();
    bool logrado = true;
    for (int b = 0; b < 4 && logrado; ++b) {
        logrado = asignarBomboAGrupos(&bombosLineales[b * 12]);
        monitor.registrarIteracion(12);
    }

    if (!logrado) {
        limpiarGrupos();
        logrado = asignarGruposPrecalculados(grupos, bombosLineales);
    }
    if (!logrado) {
        limpiarGrupos();
        logrado = asignarGruposPorConfederacion(grupos, bombosLineales);
    }
    if (!logrado) {
        limpiarGrupos();
        asignarGruposForzadosPorBombo(grupos, bombosLineales);
        logrado = true;
    }

    delete[] bombosLineales;
    gruposConformados = logrado;

    if (!gruposConformados) {
        cout << "\nNo fue posible conformar grupos.\n";
        return;
    }

    cout << "\n=== GRUPOS CONFORMADOS ===\n";
    mostrarGrupos();
}

void Torneo::mostrarGrupos() const {
    for (int i = 0; i < 12; ++i) {
        cout << "Grupo " << grupos[i]->getLetra() << ":\n";
        for (int j = 0; j < grupos[i]->getCantidadEquipos(); ++j) {
            cout << "  - " << *grupos[i]->getEquipo(j) << "\n";
        }
    }
}

int Torneo::indiceEquipo(Equipo* equipo) const {
    for (int i = 0; i < cantidadEquipos; ++i) {
        if (equipos[i] == equipo) {
            return i;
        }
    }
    return -1;
}

char Torneo::obtenerGrupoDeEquipo(Equipo* equipo) const {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < grupos[i]->getCantidadEquipos(); ++j) {
            if (grupos[i]->getEquipo(j) == equipo) {
                return grupos[i]->getLetra();
            }
        }
    }
    return '?';
}

void Torneo::generarCalendarioFaseDeGrupos() {
    liberarPartidos(partidosGrupos, 72);
    partidosGrupos = new Partido*[72];

    int capacidadPorDia[19];
    int ultimoDiaEquipo[48];
    for (int i = 0; i < 19; ++i) {
        capacidadPorDia[i] = 0;
    }
    for (int i = 0; i < 48; ++i) {
        ultimoDiaEquipo[i] = -100;
    }

    int indicePartido = 0;
    int pares[6][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};

    for (int g = 0; g < 12; ++g) {
        for (int p = 0; p < 6; ++p) {
            Equipo* a = grupos[g]->getEquipo(pares[p][0]);
            Equipo* b = grupos[g]->getEquipo(pares[p][1]);
            int idxA = indiceEquipo(a);
            int idxB = indiceEquipo(b);

            int diaElegido = 0;
            for (int dia = 0; dia < 19; ++dia) {
                bool cupo = capacidadPorDia[dia] < 4;
                bool descansoA = (dia - ultimoDiaEquipo[idxA]) >= 3;
                bool descansoB = (dia - ultimoDiaEquipo[idxB]) >= 3;
                if (cupo && descansoA && descansoB) {
                    diaElegido = dia;
                    break;
                }
            }

            Fecha fecha(20, 6, 2026);
            fecha.sumarDias(diaElegido);
            partidosGrupos[indicePartido] = new Partido();
            partidosGrupos[indicePartido]->configurar(fecha, a, b);

            capacidadPorDia[diaElegido]++;
            ultimoDiaEquipo[idxA] = diaElegido;
            ultimoDiaEquipo[idxB] = diaElegido;
            ++indicePartido;
        }
    }
}

void Torneo::simularFaseDeGrupos() {
    if (!gruposConformados) {
        conformarGrupos();
        if (!gruposConformados) {
            return;
        }
    }

    for (int i = 0; i < cantidadEquipos; ++i) {
        equipos[i]->resetDatosGrupo();
    }

    generarCalendarioFaseDeGrupos();

    cout << "\n=== FASE DE GRUPOS ===\n";
    for (int i = 0; i < 72; ++i) {
        partidosGrupos[i]->simular(false, true);
        partidosGrupos[i]->imprimirResumen();
        partidosGrupos[i]->imprimirGoleadores();
        monitor.registrarIteracion(1);
    }

    cout << "\n=== TABLAS DE CLASIFICACION ===\n";
    for (int i = 0; i < 12; ++i) {
        grupos[i]->ordenarTabla();
        grupos[i]->imprimirTabla();
    }

    faseGruposSimulada = true;
}

void Torneo::ordenarTercerLugar(Equipo** terceros, char* gruposTerceros, int cantidad) {
    for (int i = 0; i < cantidad - 1; ++i) {
        for (int j = 0; j < cantidad - i - 1; ++j) {
            if (!((*terceros[j]) > (*terceros[j + 1]))) {
                Equipo* tmpEquipo = terceros[j];
                terceros[j] = terceros[j + 1];
                terceros[j + 1] = tmpEquipo;

                char tmpGrupo = gruposTerceros[j];
                gruposTerceros[j] = gruposTerceros[j + 1];
                gruposTerceros[j + 1] = tmpGrupo;
            }
        }
    }
}

void Torneo::ordenarEquiposPorTabla(Equipo** lista, int cantidad) {
    for (int i = 0; i < cantidad - 1; ++i) {
        for (int j = 0; j < cantidad - i - 1; ++j) {
            if (!((*lista[j]) > (*lista[j + 1]))) {
                Equipo* tmp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = tmp;
            }
        }
    }
}

bool Torneo::compartenGrupo(Equipo* a, Equipo* b) const {
    return obtenerGrupoDeEquipo(a) == obtenerGrupoDeEquipo(b);
}

void Torneo::configurarDieciseisavos() {
    liberarPartidos(partidosDieciseisavos, 16);
    partidosDieciseisavos = new Partido*[16];
    for (int i = 0; i < 16; ++i) {
        partidosDieciseisavos[i] = new Partido();
    }

    Equipo* primeros[12];
    Equipo* segundos[12];
    Equipo* terceros[12];
    char gruposTerceros[12];
    for (int i = 0; i < 12; ++i) {
        primeros[i] = grupos[i]->getEquipo(0);
        segundos[i] = grupos[i]->getEquipo(1);
        terceros[i] = grupos[i]->getEquipo(2);
        gruposTerceros[i] = grupos[i]->getLetra();
    }

    ordenarEquiposPorTabla(segundos, 12);
    ordenarTercerLugar(terceros, gruposTerceros, 12);

    Equipo* mejoresTerceros[8];
    for (int i = 0; i < 8; ++i) {
        mejoresTerceros[i] = terceros[i];
    }

    bool tercerUsado[8];
    bool segundoUsado[12];
    for (int i = 0; i < 8; ++i) {
        tercerUsado[i] = false;
    }
    for (int i = 0; i < 12; ++i) {
        segundoUsado[i] = false;
    }

    Fecha fechaEliminacion(10, 7, 2026);
    int indicePartido = 0;

    for (int i = 0; i < 8; ++i) {
        int elegido = -1;
        for (int t = 0; t < 8; ++t) {
            if (!tercerUsado[t] && !compartenGrupo(primeros[i], mejoresTerceros[t])) {
                elegido = t;
                break;
            }
        }
        if (elegido == -1) {
            for (int t = 0; t < 8; ++t) {
                if (!tercerUsado[t]) {
                    elegido = t;
                    break;
                }
            }
        }
        partidosDieciseisavos[indicePartido++]->configurar(fechaEliminacion, primeros[i], mejoresTerceros[elegido]);
        tercerUsado[elegido] = true;
    }

    for (int i = 8; i < 12; ++i) {
        int elegido = -1;
        for (int s = 8; s < 12; ++s) {
            if (!segundoUsado[s] && !compartenGrupo(primeros[i], segundos[s])) {
                elegido = s;
                break;
            }
        }
        if (elegido == -1) {
            for (int s = 8; s < 12; ++s) {
                if (!segundoUsado[s]) {
                    elegido = s;
                    break;
                }
            }
        }
        partidosDieciseisavos[indicePartido++]->configurar(fechaEliminacion, primeros[i], segundos[elegido]);
        segundoUsado[elegido] = true;
    }

    Equipo* restantes[8];
    int cuentaRestantes = 0;
    for (int i = 0; i < 12; ++i) {
        if (!segundoUsado[i]) {
            restantes[cuentaRestantes++] = segundos[i];
        }
    }

    for (int i = 0; i < cuentaRestantes; i += 2) {
        int j = i + 1;
        if (j < cuentaRestantes && compartenGrupo(restantes[i], restantes[j]) && (j + 1) < cuentaRestantes) {
            Equipo* tmp = restantes[j];
            restantes[j] = restantes[j + 1];
            restantes[j + 1] = tmp;
        }
        partidosDieciseisavos[indicePartido++]->configurar(fechaEliminacion, restantes[i], restantes[j]);
    }

    repararCrucesDieciseisavos();

    cout << "\n=== PARTIDOS CONFIGURADOS PARA DIECISEISAVOS ===\n";
    for (int i = 0; i < 16; ++i) {
        partidosDieciseisavos[i]->imprimirResumen();
    }
}

void Torneo::repararCrucesDieciseisavos() {
    for (int intento = 0; intento < 16; ++intento) {
        bool huboCambio = false;

        for (int i = 0; i < 16; ++i) {
            Equipo* localI = partidosDieciseisavos[i]->getEquipo1();
            Equipo* visitanteI = partidosDieciseisavos[i]->getEquipo2();
            if (!compartenGrupo(localI, visitanteI)) {
                continue;
            }

            for (int j = 0; j < 16; ++j) {
                if (i == j) {
                    continue;
                }

                Equipo* localJ = partidosDieciseisavos[j]->getEquipo1();
                Equipo* visitanteJ = partidosDieciseisavos[j]->getEquipo2();
                if (!compartenGrupo(localI, visitanteJ) && !compartenGrupo(localJ, visitanteI)) {
                    Fecha fechaI = partidosDieciseisavos[i]->getFecha();
                    Fecha fechaJ = partidosDieciseisavos[j]->getFecha();
                    partidosDieciseisavos[i]->configurar(fechaI, localI, visitanteJ);
                    partidosDieciseisavos[j]->configurar(fechaJ, localJ, visitanteI);
                    huboCambio = true;
                    break;
                }
            }
        }

        if (!huboCambio) {
            break;
        }
    }
}

void Torneo::simularEliminatorias() {
    if (!faseGruposSimulada) {
        simularFaseDeGrupos();
        if (!faseGruposSimulada) {
            return;
        }
    }

    configurarDieciseisavos();

    cout << "\n=== DIECISEISAVOS DE FINAL ===\n";
    for (int i = 0; i < 16; ++i) {
        partidosDieciseisavos[i]->simular(true, false);
        partidosDieciseisavos[i]->imprimirResumen();
        partidosDieciseisavos[i]->imprimirGoleadores();
    }

    liberarPartidos(partidosOctavos, 8);
    partidosOctavos = new Partido*[8];
    Fecha fechaEliminacion(10, 7, 2026);
    for (int i = 0; i < 8; ++i) {
        partidosOctavos[i] = new Partido();
        partidosOctavos[i]->configurar(fechaEliminacion,
                                       partidosDieciseisavos[i * 2]->getGanador(),
                                       partidosDieciseisavos[i * 2 + 1]->getGanador());
    }

    cout << "\n=== OCTAVOS DE FINAL ===\n";
    for (int i = 0; i < 8; ++i) {
        partidosOctavos[i]->simular(true, false);
        partidosOctavos[i]->imprimirResumen();
        partidosOctavos[i]->imprimirGoleadores();
    }

    liberarPartidos(partidosCuartos, 4);
    partidosCuartos = new Partido*[4];
    for (int i = 0; i < 4; ++i) {
        partidosCuartos[i] = new Partido();
        partidosCuartos[i]->configurar(fechaEliminacion,
                                       partidosOctavos[i * 2]->getGanador(),
                                       partidosOctavos[i * 2 + 1]->getGanador());
    }

    cout << "\n=== CUARTOS DE FINAL ===\n";
    for (int i = 0; i < 4; ++i) {
        partidosCuartos[i]->simular(true, false);
        partidosCuartos[i]->imprimirResumen();
        partidosCuartos[i]->imprimirGoleadores();
    }

    liberarPartidos(partidosSemifinales, 2);
    partidosSemifinales = new Partido*[2];
    for (int i = 0; i < 2; ++i) {
        partidosSemifinales[i] = new Partido();
        partidosSemifinales[i]->configurar(fechaEliminacion,
                                           partidosCuartos[i * 2]->getGanador(),
                                           partidosCuartos[i * 2 + 1]->getGanador());
    }

    cout << "\n=== SEMIFINALES ===\n";
    for (int i = 0; i < 2; ++i) {
        partidosSemifinales[i]->simular(true, false);
        partidosSemifinales[i]->imprimirResumen();
        partidosSemifinales[i]->imprimirGoleadores();
    }

    delete partidoTercerPuesto;
    partidoTercerPuesto = new Partido();
    partidoTercerPuesto->configurar(fechaEliminacion,
                                    partidosSemifinales[0]->getPerdedor(),
                                    partidosSemifinales[1]->getPerdedor());
    cout << "\n=== TERCER PUESTO ===\n";
    partidoTercerPuesto->simular(true, false);
    partidoTercerPuesto->imprimirResumen();
    partidoTercerPuesto->imprimirGoleadores();

    delete partidoFinal;
    partidoFinal = new Partido();
    partidoFinal->configurar(fechaEliminacion,
                             partidosSemifinales[0]->getGanador(),
                             partidosSemifinales[1]->getGanador());
    cout << "\n=== FINAL ===\n";
    partidoFinal->simular(true, false);
    partidoFinal->imprimirResumen();
    partidoFinal->imprimirGoleadores();

    torneoFinalizado = true;
    guardarJugadoresActualizados();
    mostrarEstadisticasFinales();
}

const char* Torneo::confederacionConMayorPresencia(Equipo** lista, int cantidad) const {
    const char* confs[6] = {"UEFA", "CONMEBOL", "CONCACAF", "CAF", "AFC", "OFC"};
    int conteos[6] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < cantidad; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (std::strcmp(lista[i]->getConfederacion(), confs[j]) == 0) {
                ++conteos[j];
            }
        }
    }

    int mejor = 0;
    for (int i = 1; i < 6; ++i) {
        if (conteos[i] > conteos[mejor]) {
            mejor = i;
        }
    }
    return confs[mejor];
}

void Torneo::mostrarEstadisticasFinales() const {
    if (!torneoFinalizado || partidoFinal == nullptr || partidoTercerPuesto == nullptr) {
        return;
    }

    Equipo* campeon = partidoFinal->getGanador();
    Equipo* subcampeon = partidoFinal->getPerdedor();
    Equipo* tercero = partidoTercerPuesto->getGanador();
    Equipo* cuarto = partidoTercerPuesto->getPerdedor();

    Jugador* goleadorCampeon = campeon->getJugador(0);
    for (int i = 1; i < campeon->getCantidadJugadores(); ++i) {
        if (campeon->getJugador(i)->getGolesEnCopa() > goleadorCampeon->getGolesEnCopa()) {
            goleadorCampeon = campeon->getJugador(i);
        }
    }

    Jugador* top1 = nullptr;
    Jugador* top2 = nullptr;
    Jugador* top3 = nullptr;
    for (int e = 0; e < cantidadEquipos; ++e) {
        for (int j = 0; j < equipos[e]->getCantidadJugadores(); ++j) {
            Jugador* jugador = equipos[e]->getJugador(j);
            if (top1 == nullptr || jugador->getGolesEnCopa() > top1->getGolesEnCopa()) {
                top3 = top2;
                top2 = top1;
                top1 = jugador;
            } else if (top2 == nullptr || jugador->getGolesEnCopa() > top2->getGolesEnCopa()) {
                top3 = top2;
                top2 = jugador;
            } else if (top3 == nullptr || jugador->getGolesEnCopa() > top3->getGolesEnCopa()) {
                top3 = jugador;
            }
        }
    }

    Equipo* maximoHistorico = equipos[0];
    for (int i = 1; i < cantidadEquipos; ++i) {
        if (equipos[i]->getGolesFavorHistoricos() > maximoHistorico->getGolesFavorHistoricos()) {
            maximoHistorico = equipos[i];
        }
    }

    Equipo* equiposR16[32];
    for (int i = 0; i < 16; ++i) {
        equiposR16[i * 2] = partidosDieciseisavos[i]->getEquipo1();
        equiposR16[i * 2 + 1] = partidosDieciseisavos[i]->getEquipo2();
    }
    Equipo* equiposR8[16];
    for (int i = 0; i < 8; ++i) {
        equiposR8[i * 2] = partidosOctavos[i]->getEquipo1();
        equiposR8[i * 2 + 1] = partidosOctavos[i]->getEquipo2();
    }
    Equipo* equiposR4[4] = {
        partidosSemifinales[0]->getEquipo1(),
        partidosSemifinales[0]->getEquipo2(),
        partidosSemifinales[1]->getEquipo1(),
        partidosSemifinales[1]->getEquipo2()
    };

    cout << "\n=== ESTADISTICAS FINALES DEL TORNEO ===\n";
    cout << "1. " << campeon->getPais() << "\n";
    cout << "2. " << subcampeon->getPais() << "\n";
    cout << "3. " << tercero->getPais() << "\n";
    cout << "4. " << cuarto->getPais() << "\n";
    cout << "Maximo goleador del campeon: "
         << goleadorCampeon->getNombre() << " " << goleadorCampeon->getApellido()
         << " (" << goleadorCampeon->getGolesEnCopa() << ")\n";
    cout << "Top 3 goleadores de la copa:\n";
    if (top1 != nullptr) cout << "  - " << top1->getNombre() << " " << top1->getApellido() << " | " << top1->getGolesEnCopa() << "\n";
    if (top2 != nullptr) cout << "  - " << top2->getNombre() << " " << top2->getApellido() << " | " << top2->getGolesEnCopa() << "\n";
    if (top3 != nullptr) cout << "  - " << top3->getNombre() << " " << top3->getApellido() << " | " << top3->getGolesEnCopa() << "\n";
    cout << "Equipo con mas goles historicos actualizados: " << maximoHistorico->getPais()
         << " (" << maximoHistorico->getGolesFavorHistoricos() << ")\n";
    cout << "Confederacion con mayor presencia en R16: " << confederacionConMayorPresencia(equiposR16, 32) << "\n";
    cout << "Confederacion con mayor presencia en R8: " << confederacionConMayorPresencia(equiposR8, 16) << "\n";
    cout << "Confederacion con mayor presencia en R4: " << confederacionConMayorPresencia(equiposR4, 4) << "\n";
}

void Torneo::guardarJugadoresActualizados() const {
    const char* rutaEscritura = resolverRutaEscritura(ARCHIVO_JUGADORES, ARCHIVO_JUGADORES_ALT);
    std::ofstream archivo(rutaEscritura);
    archivo << "equipo,camiseta,nombre,apellido,goles_historicos,goles_copa,asistencias\n";
    for (int i = 0; i < cantidadEquipos; ++i) {
        for (int j = 0; j < equipos[i]->getCantidadJugadores(); ++j) {
            Jugador* jugador = equipos[i]->getJugador(j);
            archivo << equipos[i]->getPais() << ","
                    << jugador->getNumeroCamiseta() << ","
                    << jugador->getNombre() << ","
                    << jugador->getApellido() << ","
                    << jugador->getGolesHistoricos() << ","
                    << jugador->getGolesEnCopa() << ","
                    << jugador->getAsistencias() << "\n";
        }
    }
}

void Torneo::mostrarReporteEficiencia() const {
    long long heapEstimado = 0;
    heapEstimado += static_cast<long long>(12 * sizeof(Grupo));
    heapEstimado += static_cast<long long>(48 * sizeof(Equipo));
    heapEstimado += static_cast<long long>(48 * 26 * sizeof(Jugador));
    heapEstimado += static_cast<long long>(104 * sizeof(Partido));

    long long stackEstimado = sizeof(*this);
    stackEstimado += static_cast<long long>(sizeof(Equipo*) * 48);
    stackEstimado += static_cast<long long>(sizeof(Equipo*) * 12 * 3);
    stackEstimado += static_cast<long long>(sizeof(bool) * 48);
    stackEstimado += static_cast<long long>(sizeof(int) * 32);

    cout << "\n=== REPORTE DE EFICIENCIA ===\n";
    cout << "Iteraciones acumuladas: " << monitor.getIteraciones() << "\n";
    cout << "Memoria heap estimada: " << heapEstimado << " bytes\n";
    cout << "Memoria stack estimada: " << stackEstimado << " bytes\n";
    cout << "Incluye variables locales, arreglos auxiliares y parametros por valor usados en la funcionalidad.\n";
}

void Torneo::ejecutarMenu() {
    int opcion = -1;
    do {
        cout << "\n===== UdeAWorldCup =====\n";
        cout << "1. Cargar / actualizar datos\n";
        cout << "2. Conformar grupos\n";
        cout << "3. Simular fase de grupos\n";
        cout << "4. Simular torneo completo\n";
        cout << "5. Reporte de eficiencia\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cargarOActualizarDatos();
            mostrarReporteEficiencia();
            break;
        case 2:
            conformarGrupos();
            mostrarReporteEficiencia();
            break;
        case 3:
            simularFaseDeGrupos();
            mostrarReporteEficiencia();
            break;
        case 4:
            simularEliminatorias();
            mostrarReporteEficiencia();
            break;
        case 5:
            mostrarReporteEficiencia();
            break;
        case 0:
            cout << "Saliendo del sistema.\n";
            break;
        default:
            cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 0);
}
