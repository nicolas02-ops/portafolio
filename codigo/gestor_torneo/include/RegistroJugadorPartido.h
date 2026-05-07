#ifndef REGISTROJUGADORPARTIDO_H
#define REGISTROJUGADORPARTIDO_H

#include "EstadisticaPartido.h"
#include "Jugador.h"

class RegistroJugadorPartido {
private:
    Jugador* jugador;
    int asistencias;
    EstadisticaPartido estadistica;

public:
    RegistroJugadorPartido();

    void configurar(Jugador* jugadorPartido);
    void registrarGol();
    void registrarAmarilla();
    void registrarRoja();
    void registrarFalta();
    void registrarAsistencia();
    void setMinutosJugados(int minutos);
    void aplicarAHistoricos();

    Jugador* getJugador() const;
    int getGoles() const;
    int getAmarillas() const;
    int getRojas() const;
    int getFaltas() const;
    int getMinutosJugados() const;
    int getAsistencias() const;
};

#endif // REGISTROJUGADORPARTIDO_H
