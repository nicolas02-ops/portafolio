#ifndef GRUPO_H
#define GRUPO_H

#include "Equipo.h"

class Grupo {
private:
    char letra;
    Equipo** equipos;
    int cantidadEquipos;

public:
    Grupo();
    ~Grupo();

    void setLetra(char idGrupo);
    char getLetra() const;
    bool puedeAgregarEquipo(Equipo* equipo) const;
    void agregarEquipo(Equipo* equipo);
    void agregarEquipoForzado(Equipo* equipo);
    void quitarUltimoEquipo();
    void ordenarTabla();
    void intercambiarEquipos(int a, int b);
    Equipo* getEquipo(int idx) const;
    int getCantidadEquipos() const;
    void imprimirTabla() const;
};

#endif // GRUPO_H
