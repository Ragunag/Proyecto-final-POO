#include "Habitacion.h"
#include <iostream>

Habitacion::Habitacion(std::string nombre, std::string descripcion) {
    this->nombre = nombre;
    this->descripcion = descripcion;
    for (int i = 0; i < 4; i++) {
        salidas[i] = nullptr;
    }
}

Habitacion::~Habitacion() {
    for (size_t i = 0; i < enemigos.size(); i++) {
        delete enemigos[i];
    }
}

void Habitacion::agregarEnemigo(Enemigo* enemigo) {
    enemigos.push_back(enemigo);
}

void Habitacion::agregarObjeto(Objeto objeto) {
    objetos.push_back(objeto);
}

void Habitacion::conectarSalida(int direccion, Habitacion* habitacion) {
    if (direccion >= 0 && direccion < 4) {
        salidas[direccion] = habitacion;
    }
}

std::string Habitacion::getNombre() {
    return nombre;
}

std::string Habitacion::getDescripcion() {
    return descripcion;
}

void Habitacion::mostrarInfo() {
    std::cout << "\n============================================" << std::endl;
    std::cout << "UBICACION: " << nombre << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << descripcion << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    if (enemigos.size() > 0) {
        std::cout << "\n[!] ENEMIGOS EN ESTA ZONA:" << std::endl;
        for (size_t i = 0; i < enemigos.size(); i++) {
            std::cout << "  " << (i+1) << ". " << enemigos[i]->getNombre() << std::endl;
            std::cout << "     HP: " << enemigos[i]->getVida() << "/" << enemigos[i]->getVidaMaxima()
                      << " | ATK: " << enemigos[i]->getAtaque()
                      << " | DEF: " << enemigos[i]->getDefensa() << std::endl;
        }
    } else {
        std::cout << "\n[✓] Area segura - No hay enemigos" << std::endl;
    }

    if (objetos.size() > 0) {
        std::cout << "\n[*] OBJETOS DISPONIBLES:" << std::endl;
        for (size_t i = 0; i < objetos.size(); i++) {
            std::cout << "  - " << objetos[i].getNombre();
            if (objetos[i].getTipo() == "curacion") {
                std::cout << " (+" << objetos[i].getValor() << " HP)";
            } else if (objetos[i].getTipo() == "arma") {
                std::cout << " (+" << objetos[i].getValor() << " ATK)";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\n[→] SALIDAS DISPONIBLES:" << std::endl;
    if (salidas[0] != nullptr) std::cout << "  - Norte: " << salidas[0]->getNombre() << std::endl;
    if (salidas[1] != nullptr) std::cout << "  - Sur: " << salidas[1]->getNombre() << std::endl;
    if (salidas[2] != nullptr) std::cout << "  - Este: " << salidas[2]->getNombre() << std::endl;
    if (salidas[3] != nullptr) std::cout << "  - Oeste: " << salidas[3]->getNombre() << std::endl;
    std::cout << "============================================" << std::endl;
}

bool Habitacion::tieneEnemigos() {
    return enemigos.size() > 0;
}

std::vector<Enemigo*>& Habitacion::getEnemigos() {
    return enemigos;
}

std::vector<Objeto>& Habitacion::getObjetos() {
    return objetos;
}

Habitacion* Habitacion::getSalida(int direccion) {
    if (direccion >= 0 && direccion < 4) {
        return salidas[direccion];
    }
    return nullptr;
}