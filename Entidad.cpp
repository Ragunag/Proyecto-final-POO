#include "Entidad.h"
#include <iostream>

Entidad::Entidad(std::string nombre, int vida, int ataque, int defensa) {
    this->nombre = nombre;
    this->vida = vida;
    this->vidaMaxima = vida;
    this->ataque = ataque;
    this->defensa = defensa;
}

Entidad::~Entidad() { }

std::string Entidad::getNombre() {
    return nombre;
}

int Entidad::getVida() {
    return vida;
}

int Entidad::getVidaMaxima() {
    return vidaMaxima;
}

int Entidad::getAtaque() {
    return ataque;
}

int Entidad::getDefensa() {
    return defensa;
}

void Entidad::setVida(int nuevaVida) {
    vida = nuevaVida;
    if (vida > vidaMaxima) {
        vida = vidaMaxima;
    }
    if (vida < 0) {
        vida = 0;
    }
}

void Entidad::setVidaMaxima(int nuevaVidaMax) {
    vidaMaxima = nuevaVidaMax;
    if (vida > vidaMaxima) {
        vida = vidaMaxima;
    }
}

void Entidad::setDefensa(int nuevaDefensa) {
    defensa = nuevaDefensa;
    if (defensa < 0) {
        defensa = 0;
    }
}

void Entidad::recibirDanio(int danio) {
    int danioReal = danio - defensa;
    if (danioReal < 0) {
        danioReal = 0;
    }
    vida = vida - danioReal;
    if (vida < 0) {
        vida = 0;
    }
}

bool Entidad::estaVivo() {
    return vida > 0;
}