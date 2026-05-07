#ifndef MONITORRECURSOS_H
#define MONITORRECURSOS_H

class MonitorRecursos {
private:
    long int contadorIteraciones;
    double memoriaHeap;
    double memoriaStack;

public:
    MonitorRecursos();

    void registrarIteracion(int n);
    void calcularConsumoMemoria();
    void reset();

    long int getIteraciones() const;
    double getMemoriaHeap() const;
    double getMemoriaStack() const;
    void setMemoriaEstimada(double heapBytes, double stackBytes);
};

#endif // MONITORRECURSOS_H
