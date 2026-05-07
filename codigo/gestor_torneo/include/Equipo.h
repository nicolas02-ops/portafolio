#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include "Jugador.h"

class Equipo {
private:
    char* pais;
    char* confederacion;
    int rankingFIFA;
    Jugador** plantilla;
    int cantidadJugadores;

    int puntosGrupo;
    int golesFavorGrupo;
    int golesContraGrupo;

    int golesFavorHistoricos;
    int golesContraHistoricos;
    int partidosGanadosHistoricos;
    int partidosEmpatadosHistoricos;
    int partidosPerdidosHistoricos;
    int tarjetasAmarillasHistoricas;
    int tarjetasRojasHistoricas;
    int faltasHistoricas;

    void liberarCadena(char*& texto);
    void liberarPlantilla();
    void copiarDesde(const Equipo& otro);
    void copiarCadena(char*& destino, const char* origen);

public:
    Equipo();
    Equipo(const Equipo& otro);
    Equipo& operator=(const Equipo& otro);
    ~Equipo();

    void configurar(const char* paisEquipo,
                    const char* confederacionEquipo,
                    int rankingEquipo,
                    int gfHistoricos,
                    int gcHistoricos,
                    int ganados,
                    int empatados,
                    int perdidos);
    void crearPlantillaArtificial(int cantidad = 26);
    void registrarResultadoGrupo(int golesFavor, int golesContra);
    void registrarResultadoHistorico(int golesFavor, int golesContra);
    void registrarDisciplinaHistorica(int amarillas, int rojas, int faltasCometidas);
    void resetDatosGrupo();

    const char* getPais() const;
    const char* getConfederacion() const;
    int getRankingFIFA() const;
    int getPuntosGrupo() const;
    int getDiferenciaGoles() const;
    int getGolesFavor() const;
    int getGolesContraGrupo() const;
    int getGolesFavorHistoricos() const;
    int getGolesContraHistoricos() const;
    int getPartidosHistoricos() const;
    double getPromedioGolesFavor() const;
    double getPromedioGolesContra() const;
    int getCantidadJugadores() const;
    Jugador* getJugador(int idx) const;

    bool operator>(const Equipo& otro) const;
    friend std::ostream& operator<<(std::ostream& os, const Equipo& e);
};

#endif // EQUIPO_H
