#ifndef FECHA_H
#define FECHA_H

#include <iostream>

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha();
    Fecha(int d, int m, int a);

    void configurar(int d, int m, int a);
    void sumarDias(int dias);
    int diferenciaDias(const Fecha& otra) const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    friend std::ostream& operator<<(std::ostream& os, const Fecha& fecha);
};

#endif // FECHA_H
