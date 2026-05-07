#include "board.h"
#include <iostream>

int tablero_ancho = 0;
int tablero_alto = 0;
int tablero_bytes_por_fila = 0;
unsigned char** tablero_datos = 0;
using namespace std;

int crear_tablero(int ancho, int alto) {
    if (ancho < 8 || alto < 8 || ancho % 8 != 0) {
        return 0;
    }

    if (tablero_datos != 0) {
        destruir_tablero();
    }

    tablero_ancho = ancho;
    tablero_alto = alto;
    tablero_bytes_por_fila = ancho / 8;
    tablero_datos = new unsigned char*[alto];

    for (int i = 0; i < alto; i++) {
        tablero_datos[i] = new unsigned char[tablero_bytes_por_fila];
    }

    limpiar_tablero();
    return 1;
}

void destruir_tablero() {
    if (tablero_datos == 0) {
        return;
    }

    for (int i = 0; i < tablero_alto; i++) {
        delete[] tablero_datos[i];
    }

    delete[] tablero_datos;
    tablero_datos = 0;
    tablero_ancho = 0;
    tablero_alto = 0;
    tablero_bytes_por_fila = 0;
}

int obtener_ancho_tablero() {
    return tablero_ancho;
}

int obtener_alto_tablero() {
    return tablero_alto;
}

int obtener_bytes_por_fila_tablero() {
    return tablero_bytes_por_fila;
}

int obtener_bit(int fila, int columna) {
    if (fila < 0 || fila >= tablero_alto || columna < 0 || columna >= tablero_ancho) {
        return 0;
    }

    int indice_byte = columna / 8;
    int indice_bit = 7 - (columna % 8);
    return (tablero_datos[fila][indice_byte] >> indice_bit) & 1;
}

void establecer_bit(int fila, int columna, int valor) {
    if (fila < 0 || fila >= tablero_alto || columna < 0 || columna >= tablero_ancho) {
        return;
    }

    int indice_byte = columna / 8;
    int indice_bit = 7 - (columna % 8);

    if (valor) {
        tablero_datos[fila][indice_byte] |= (1 << indice_bit);
    } else {
        tablero_datos[fila][indice_byte] &= ~(1 << indice_bit);
    }
}

void limpiar_tablero() {
    for (int i = 0; i < tablero_alto; i++) {
        for (int j = 0; j < tablero_bytes_por_fila; j++) {
            tablero_datos[i][j] = 0;
        }
    }
}

void imprimir_tablero() {
    cout << "\n+";
    for (int i = 0; i < tablero_ancho; i++) {
        cout << "-";
    }
    cout << "+\n";

    for (int fila = 0; fila < tablero_alto; fila++) {
        cout << "|";
        for (int columna = 0; columna < tablero_ancho; columna++) {
            cout << (obtener_bit(fila, columna) ? "#" : ".");
        }
        cout << "|\n";
    }

    cout << "+";
    for (int i = 0; i < tablero_ancho; i++) {
        cout << "-";
    }
    cout << "+\n";
}

int limpiar_lineas_completas() {
    int lineas_eliminadas = 0;
    int fila = tablero_alto - 1;

    while (fila >= 0) {
        int completa = 1;

        for (int byte = 0; byte < tablero_bytes_por_fila; byte++) {
            if (tablero_datos[fila][byte] != 0xFF) {
                completa = 0;
                break;
            }
        }

        if (completa) {
            unsigned char* fila_temporal = tablero_datos[fila];

            for (int r = fila; r > 0; r--) {
                tablero_datos[r] = tablero_datos[r - 1];
            }

            tablero_datos[0] = fila_temporal;

            for (int byte = 0; byte < tablero_bytes_por_fila; byte++) {
                tablero_datos[0][byte] = 0;
            }

            lineas_eliminadas++;
        } else {
            fila--;
        }
    }

    return lineas_eliminadas;
}
