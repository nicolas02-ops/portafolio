
#include "pieces.h"

using namespace std;

int indice_pieza = 0;

void obtener_pieza_inicial(int tipo, unsigned short forma[4], int* ancho, int* alto) {
    for (int i = 0; i < 4; i++) {
        forma[i] = 0;
    }

    switch (tipo) {
    case 0:
        forma[0] = 0b1111000000000000;
        *ancho = 4;
        *alto = 1;
        break;
    case 1:
        forma[0] = 0b1100000000000000;
        forma[1] = 0b1100000000000000;
        *ancho = 2;
        *alto = 2;
        break;
    case 2:
        forma[0] = 0b1110000000000000;
        forma[1] = 0b0100000000000000;
        *ancho = 3;
        *alto = 2;
        break;
    case 3:
        forma[0] = 0b0110000000000000;
        forma[1] = 0b1100000000000000;
        *ancho = 3;
        *alto = 2;
        break;
    case 4:
        forma[0] = 0b1100000000000000;
        forma[1] = 0b0110000000000000;
        *ancho = 3;
        *alto = 2;
        break;
    case 5:
        forma[0] = 0b1000000000000000;
        forma[1] = 0b1110000000000000;
        *ancho = 3;
        *alto = 2;
        break;
    case 6:
        forma[0] = 0b0010000000000000;
        forma[1] = 0b1110000000000000;
        *ancho = 3;
        *alto = 2;
        break;
    default:
        *ancho = 0;
        *alto = 0;
        break;
    }
}

void rotar_forma_pieza(const unsigned short forma_entrada[4], int ancho_entrada, int alto_entrada,
                       unsigned short forma_salida[4], int* ancho_salida, int* alto_salida) {
    for (int i = 0; i < 4; i++) {
        forma_salida[i] = 0;
    }

    int bits[4][4] = {{0}};

    for (int fila = 0; fila < alto_entrada; fila++) {
        unsigned short fila_actual = forma_entrada[fila];
        for (int columna = 0; columna < ancho_entrada; columna++) {
            if (fila_actual & (1 << (15 - columna))) {
                bits[fila][columna] = 1;
            }
        }
    }
    
    for (int fila = 0; fila < alto_entrada; fila++) {
        for (int columna = 0; columna < ancho_entrada; columna++) {
            if (bits[fila][columna]) {
                int nueva_fila = columna;
                int nueva_columna = alto_entrada - 1 - fila;
                forma_salida[nueva_fila] |= (1 << (15 - nueva_columna));
            }
        }
    }

    *ancho_salida = alto_entrada;
    *alto_salida = ancho_entrada;
}

int pieza_aleatoria() {
    int pieza = indice_pieza;
    indice_pieza = indice_pieza + 1;

    if (indice_pieza == 7) {
        indice_pieza = 0;
    }

    return pieza;
}
