#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
private:
    char* nombre;
    char* apellido;
    int numeroCamiseta;
    int golesHistoricos;
    int partidosJugados;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int minutosJugados;
    int asistencias;
    int golesEnCopa;

    void liberarCadena(char*& texto);
    void copiarCadena(char*& destino, const char* origen);

public:
    Jugador();
    Jugador(const Jugador& otro);
    Jugador& operator=(const Jugador& otro);
    ~Jugador();

    void configurar(const char* nombreJugador, const char* apellidoJugador, int dorsalJugador, int golesIniciales = 0);

    const char* getNombre() const;
    const char* getApellido() const;
    int getNumeroCamiseta() const;
    int getGolesHistoricos() const;
    int getGolesEnCopa() const;
    int getAsistencias() const;

    void sumarGol();
    void sumarPartido();
    void sumarMinutos(int minutos);
    void sumarAmarilla();
    void sumarRoja();
    void sumarFalta();
    void sumarAsistencia();

    void imprimir() const;
};

#endif // JUGADOR_H
