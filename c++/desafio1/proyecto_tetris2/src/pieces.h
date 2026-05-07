#ifndef PIECES_H
#define PIECES_H
/*
#define MAX_TAMANO_PIEZA 4
#define NUMERO_PIEZAS 7
*/
void obtener_pieza_inicial(int tipo, unsigned short forma[4], int* ancho, int* alto);

void rotar_forma_pieza(const unsigned short forma_entrada[4], int ancho_entrada, int alto_entrada,
                       unsigned short forma_salida[4], int* ancho_salida, int* alto_salida);

int pieza_aleatoria();

#endif
