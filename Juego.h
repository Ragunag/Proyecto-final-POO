#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Habitacion.h"
#include <vector>

class Juego {
private:
    Jugador* jugador;
    Habitacion* habitacionActual;
    std::vector<Habitacion*> habitaciones;
    bool juegoActivo;

    void crearMundo();
    void combate();
    void moverJugador(int direccion);
    void recogerObjetos();
    void mostrarMenu();

public:
    Juego();
    ~Juego();

    void iniciar();
    void ejecutar();
};

#endif