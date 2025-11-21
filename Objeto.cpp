#include "Objeto.h"
#include <iostream>

Objeto::Objeto(std::string nombre, std::string tipo, int valor) {
    this->nombre = nombre;
    this->tipo = tipo;
    this->valor = valor;
}

std::string Objeto::getNombre() {
    return nombre;
}

std::string Objeto::getTipo() {
    return tipo;
}

int Objeto::getValor() {
    return valor;
}

void Objeto::mostrarInfo() {
    std::cout << nombre << " (" << tipo << ") - ";
    if (tipo == "curacion") {
        std::cout << "Cura " << valor << " HP";
    } else if (tipo == "arma") {
        std::cout << "+" << valor << " Ataque";
    }
    std::cout << std::endl;
}