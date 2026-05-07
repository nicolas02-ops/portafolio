#ifndef BOARD_H
#define BOARD_H

int crear_tablero(int ancho, int alto);
void destruir_tablero();

int obtener_ancho_tablero();
int obtener_alto_tablero();
int obtener_bytes_por_fila_tablero();

int obtener_bit(int fila, int columna);
void establecer_bit(int fila, int columna, int valor);

void limpiar_tablero();
void imprimir_tablero();
int limpiar_lineas_completas();

#endif
