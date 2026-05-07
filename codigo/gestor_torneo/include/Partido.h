#ifndef PARTIDO_H
#define PARTIDO_H

#include "Equipo.h"
#include "Fecha.h"
#include "RegistroJugadorPartido.h"

class Partido {
private:
    Fecha fecha;
    Equipo* equipo1;
    Equipo* equipo2;
    char sede[20];
    char hora[6];
    char arbitros[3][20];
    RegistroJugadorPartido* convocados1;
    RegistroJugadorPartido* convocados2;
    int goles1;
    int goles2;
    double posesion1;
    double posesion2;
    bool huboProrroga;

    void liberarConvocados();
    void prepararConvocados(Equipo* equipo, RegistroJugadorPartido*& convocados);
    int calcularGolesEsperados(Equipo* atacante, Equipo* defensor) const;
    void asignarEventosEquipo(RegistroJugadorPartido* convocados, int golesEquipo, int minutosPorJugador);
    void actualizarHistoricos(bool faseDeGrupos);
    double generarAleatorio01() const;

public:
    Partido();
    ~Partido();

    void configurar(const Fecha& fechaPartido, Equipo* primerEquipo, Equipo* segundoEquipo);
    void simular(bool eliminacionDirecta, bool faseDeGrupos);

    int getGolesEquipo1() const;
    int getGolesEquipo2() const;
    Equipo* getEquipo1() const;
    Equipo* getEquipo2() const;
    Equipo* getGanador() const;
    Equipo* getPerdedor() const;
    const Fecha& getFecha() const;
    bool getHuboProrroga() const;
    void imprimirResumen() const;
    void imprimirGoleadores() const;
};

#endif // PARTIDO_H
