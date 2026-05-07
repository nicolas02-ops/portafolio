#include "MonitorRecursos.h"

MonitorRecursos::MonitorRecursos() : contadorIteraciones(0), memoriaHeap(0.0), memoriaStack(0.0) {}

void MonitorRecursos::registrarIteracion(int n) { contadorIteraciones += n; }

void MonitorRecursos::calcularConsumoMemoria() {
    if (memoriaHeap < 0.0) {
        memoriaHeap = 0.0;
    }
    if (memoriaStack < 0.0) {
        memoriaStack = 0.0;
    }
}

void MonitorRecursos::reset() {
    contadorIteraciones = 0;
    memoriaHeap = 0.0;
    memoriaStack = 0.0;
}

long int MonitorRecursos::getIteraciones() const { return contadorIteraciones; }

double MonitorRecursos::getMemoriaHeap() const { return memoriaHeap; }

double MonitorRecursos::getMemoriaStack() const { return memoriaStack; }

void MonitorRecursos::setMemoriaEstimada(double heapBytes, double stackBytes) {
    memoriaHeap = heapBytes;
    memoriaStack = stackBytes;
}
