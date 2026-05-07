#ifndef TORNEO_H
#define TORNEO_H

#include "Grupo.h"
#include "MonitorRecursos.h"
#include "Partido.h"

class Torneo {
private:
    Grupo** grupos;
    Equipo** equipos;
    int cantidadEquipos;
    MonitorRecursos monitor;
    Partido** partidosGrupos;
    Partido** partidosDieciseisavos;
    Partido** partidosOctavos;
    Partido** partidosCuartos;
    Partido** partidosSemifinales;
    Partido* partidoTercerPuesto;
    Partido* partidoFinal;

    bool datosCargados;
    bool gruposConformados;
    bool faseGruposSimulada;
    bool torneoFinalizado;

    void crearArchivoBaseSiNoExiste();
    void liberarPartidos(Partido**& lista, int cantidad);
    void cargarEquiposDesdeCSV();
    void cargarOActualizarDatos();
    void crearBombos(Equipo*** bombos);
    void limpiarGrupos();
    bool asignarBomboAGrupos(Equipo** bombo);
    void conformarGrupos();
    void mostrarGrupos() const;
    void generarCalendarioFaseDeGrupos();
    int indiceEquipo(Equipo* equipo) const;
    char obtenerGrupoDeEquipo(Equipo* equipo) const;
    void simularFaseDeGrupos();
    void ordenarTercerLugar(Equipo** terceros, char* gruposTerceros, int cantidad);
    void ordenarEquiposPorTabla(Equipo** lista, int cantidad);
    bool compartenGrupo(Equipo* a, Equipo* b) const;
    void configurarDieciseisavos();
    void repararCrucesDieciseisavos();
    void simularEliminatorias();
    void mostrarEstadisticasFinales() const;
    void guardarJugadoresActualizados() const;
    const char* confederacionConMayorPresencia(Equipo** lista, int cantidad) const;

public:
    Torneo();
    ~Torneo();

    void ejecutarMenu();
    void mostrarReporteEficiencia() const;
};

#endif // TORNEO_H
