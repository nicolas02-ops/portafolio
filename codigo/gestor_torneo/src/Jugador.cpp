#include "Jugador.h"
#include <iostream>

using namespace std;

Jugador::Jugador()
    : nombre(nullptr),
      apellido(nullptr),
      numeroCamiseta(0),
      golesHistoricos(0),
      partidosJugados(0),
      tarjetasAmarillas(0),
      tarjetasRojas(0),
      faltas(0),
      minutosJugados(0),
      asistencias(0),
      golesEnCopa(0) {
    copiarCadena(nombre, "");
    copiarCadena(apellido, "");
}

Jugador::Jugador(const Jugador& otro)
    : nombre(nullptr),
      apellido(nullptr),
      numeroCamiseta(otro.numeroCamiseta),
      golesHistoricos(otro.golesHistoricos),
      partidosJugados(otro.partidosJugados),
      tarjetasAmarillas(otro.tarjetasAmarillas),
      tarjetasRojas(otro.tarjetasRojas),
      faltas(otro.faltas),
      minutosJugados(otro.minutosJugados),
      asistencias(otro.asistencias),
      golesEnCopa(otro.golesEnCopa) {
    copiarCadena(nombre, otro.nombre != nullptr ? otro.nombre : "");
    copiarCadena(apellido, otro.apellido != nullptr ? otro.apellido : "");
}

Jugador& Jugador::operator=(const Jugador& otro) {
    if (this != &otro) {
        liberarCadena(nombre);
        liberarCadena(apellido);
        copiarCadena(nombre, otro.nombre != nullptr ? otro.nombre : "");
        copiarCadena(apellido, otro.apellido != nullptr ? otro.apellido : "");
        numeroCamiseta = otro.numeroCamiseta;
        golesHistoricos = otro.golesHistoricos;
        partidosJugados = otro.partidosJugados;
        tarjetasAmarillas = otro.tarjetasAmarillas;
        tarjetasRojas = otro.tarjetasRojas;
        faltas = otro.faltas;
        minutosJugados = otro.minutosJugados;
        asistencias = otro.asistencias;
        golesEnCopa = otro.golesEnCopa;
    }
    return *this;
}

Jugador::~Jugador() {
    liberarCadena(nombre);
    liberarCadena(apellido);
}

void Jugador::liberarCadena(char*& texto) {
    if (texto != nullptr) {
        delete[] texto;
        texto = nullptr;
    }
}

void Jugador::copiarCadena(char*& destino, const char* origen) {
    int tam = 0;
    while (origen[tam] != '\0') {
        ++tam;
    }

    destino = new char[tam + 1];
    for (int i = 0; i < tam; ++i) {
        destino[i] = origen[i];
    }
    destino[tam] = '\0';
}

void Jugador::configurar(const char* nombreJugador, const char* apellidoJugador, int dorsalJugador, int golesIniciales) {
    liberarCadena(nombre);
    liberarCadena(apellido);
    copiarCadena(nombre, nombreJugador != nullptr ? nombreJugador : "");
    copiarCadena(apellido, apellidoJugador != nullptr ? apellidoJugador : "");
    numeroCamiseta = dorsalJugador;
    golesHistoricos = golesIniciales;
    partidosJugados = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    minutosJugados = 0;
    asistencias = 0;
    golesEnCopa = 0;
}

const char* Jugador::getNombre() const { return (nombre != nullptr) ? nombre : ""; }

const char* Jugador::getApellido() const { return (apellido != nullptr) ? apellido : ""; }

int Jugador::getNumeroCamiseta() const { return numeroCamiseta; }

int Jugador::getGolesHistoricos() const { return golesHistoricos; }

int Jugador::getGolesEnCopa() const { return golesEnCopa; }

int Jugador::getAsistencias() const { return asistencias; }

void Jugador::sumarGol() {
    ++golesHistoricos;
    ++golesEnCopa;
}

void Jugador::sumarPartido() { ++partidosJugados; }

void Jugador::sumarMinutos(int minutos) { minutosJugados += minutos; }

void Jugador::sumarAmarilla() { ++tarjetasAmarillas; }

void Jugador::sumarRoja() { ++tarjetasRojas; }

void Jugador::sumarFalta() { ++faltas; }

void Jugador::sumarAsistencia() { ++asistencias; }

void Jugador::imprimir() const {
    cout << numeroCamiseta << " - " << getNombre() << " " << getApellido()
         << " | Goles hist: " << golesHistoricos
         << " | Asistencias: " << asistencias
         << " | Goles copa: " << golesEnCopa << "\n";
}
