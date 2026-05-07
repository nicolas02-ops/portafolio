#ifndef ESTADISTICAHISTORICA_H
#define ESTADISTICAHISTORICA_H

class EstadisticaHistorica {
private:
    int mundialesGanados;
    float promedioGoles;
    int golesFavor;
    int golesContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int puntosGrupo;

public:
    EstadisticaHistorica();

    void actualizarDatos(int golesAFavor, int golesEnContra);
    void resetGrupo();

    int getPuntosGrupo() const;
    int getDiferenciaGoles() const;
    int getGolesFavor() const;
    float getPromedioGoles() const;
};

#endif // ESTADISTICAHISTORICA_H
