#ifndef ESTADISTICAPARTIDO_H
#define ESTADISTICAPARTIDO_H

class EstadisticaPartido {
private:
    int goles;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int minutosJugados;

public:
    EstadisticaPartido();

    void reset();
    void registrarGol();
    void registrarAmarilla();
    void registrarRoja();
    void registrarFalta();
    void setMinutosJugados(int minutos);

    int getGoles() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;
    int getMinutosJugados() const;
};

#endif // ESTADISTICAPARTIDO_H
