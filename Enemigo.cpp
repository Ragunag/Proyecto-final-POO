#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo(std::string nombre, std::string tipo, int vida, int ataque, int defensa)
    : Entidad(nombre, vida, ataque, defensa) {
    this->tipo = tipo;
}

void Enemigo::atacar(Entidad* objetivo) {
    std::cout << "\n[ATAQUE ENEMIGO] " << nombre << " -> " << objetivo->getNombre() << std::endl;
    std::cout << "Stats atacante: ATK=" << ataque << " | Tipo=" << tipo << std::endl;
    std::cout << "Stats objetivo: DEF=" << objetivo->getDefensa()
              << " | HP=" << objetivo->getVida() << "/" << objetivo->getVidaMaxima() << std::endl;

    int defensaObjetivo = objetivo->getDefensa();
    int danioReal = ataque - defensaObjetivo;
    if (danioReal < 0) danioReal = 0;

    objetivo->recibirDanio(ataque);

    std::cout << ">>> Danio recibido: " << danioReal
              << " (ATK:" << ataque << " - DEF:" << defensaObjetivo << ")" << std::endl;
    std::cout << ">>> Tu HP restante: " << objetivo->getVida()
              << "/" << objetivo->getVidaMaxima() << std::endl;
}

void Enemigo::mostrarEstado() {
    std::cout << nombre << " (" << tipo << ")" << std::endl;
    std::cout << "   HP: " << vida << "/" << vidaMaxima
              << " | ATK: " << ataque << " | DEF: " << defensa << std::endl;
}

std::string Enemigo::getTipo() {
    return tipo;
}