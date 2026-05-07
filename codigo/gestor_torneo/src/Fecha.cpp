#include "Fecha.h"

Fecha::Fecha() : dia(1), mes(1), anio(2026) {}

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

void Fecha::configurar(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}

void Fecha::sumarDias(int dias) {
    static const int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    dia += dias;
    while (dia > diasPorMes[mes - 1]) {
        dia -= diasPorMes[mes - 1];
        ++mes;
        if (mes > 12) {
            mes = 1;
            ++anio;
        }
    }
}

int Fecha::diferenciaDias(const Fecha& otra) const {
    int totalActual = anio * 365 + mes * 30 + dia;
    int totalOtra = otra.anio * 365 + otra.mes * 30 + otra.dia;
    return totalActual - totalOtra;
}

int Fecha::getDia() const { return dia; }

int Fecha::getMes() const { return mes; }

int Fecha::getAnio() const { return anio; }

std::ostream& operator<<(std::ostream& os, const Fecha& fecha) {
    if (fecha.dia < 10) {
        os << '0';
    }
    os << fecha.dia << '/';
    if (fecha.mes < 10) {
        os << '0';
    }
    os << fecha.mes << '/' << fecha.anio;
    return os;
}
