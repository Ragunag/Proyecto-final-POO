#include "Jugador.h"
#include <iostream>

Jugador::Jugador(std::string nombre) : Entidad(nombre, 100, 15, 5) {
    accionPuntos = 0;
    empatiaPuntos = 0;
    sacrificioPuntos = 0;
}

void Jugador::atacar(Entidad* objetivo) {
    std::cout << "\n[ATAQUE] " << nombre << " -> " << objetivo->getNombre() << std::endl;
    std::cout << "Stats atacante: ATK=" << ataque << std::endl;
    std::cout << "Stats objetivo: DEF=" << objetivo->getDefensa() << " | HP=" << objetivo->getVida() << "/" << objetivo->getVidaMaxima() << std::endl;

    int defensaObjetivo = objetivo->getDefensa();
    int danioReal = ataque - defensaObjetivo;
    if (danioReal < 0) danioReal = 0;

    objetivo->recibirDanio(ataque);

    std::cout << ">>> Danio infligido: " << danioReal << " (ATK:" << ataque << " - DEF:" << defensaObjetivo << ")" << std::endl;
    std::cout << ">>> HP restante del objetivo: " << objetivo->getVida() << "/" << objetivo->getVidaMaxima() << std::endl;
}

void Jugador::mostrarEstado() {
    std::cout << "\n========== ESTADO DE " << nombre << " ==========" << std::endl;
    std::cout << "HP: " << vida << "/" << vidaMaxima << " | ATK: " << ataque << " | DEF: " << defensa << std::endl;
    std::cout << "Puntos de Accion: " << accionPuntos << std::endl;
    std::cout << "Puntos de Empatia: " << empatiaPuntos << std::endl;
    std::cout << "Puntos de Sacrificio: " << sacrificioPuntos << std::endl;
    std::cout << "Objetos en inventario: " << inventario.size() << std::endl;
    std::cout << "========================================" << std::endl;
}

void Jugador::agregarObjeto(Objeto objeto) {
    inventario.push_back(objeto);
    std::cout << "Objeto agregado: " << objeto.getNombre() << std::endl;
}

void Jugador::mostrarInventario() {
    std::cout << "\n============================================" << std::endl;
    std::cout << "              INVENTARIO                    " << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Stats actuales: HP=" << vida << "/" << vidaMaxima
              << " | ATK=" << ataque << " | DEF=" << defensa << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    if (inventario.size() == 0) {
        std::cout << "[Inventario vacio]" << std::endl;
    } else {
        std::cout << "Objetos disponibles:" << std::endl;
        for (size_t i = 0; i < inventario.size(); i++) {
            std::cout << "  " << (i + 1) << ". ";
            inventario[i].mostrarInfo();
        }
    }
    std::cout << "============================================" << std::endl;
}

void Jugador::usarObjeto(int indice) {
    if (indice < 0 || indice >= static_cast<int>(inventario.size())) {
        std::cout << "Objeto no valido" << std::endl;
        return;
    }

    Objeto obj = inventario[indice];

    std::cout << "\n[USO DE OBJETO]" << std::endl;
    std::cout << "Stats antes: HP=" << vida << "/" << vidaMaxima
              << " | ATK=" << ataque << " | DEF=" << defensa << std::endl;

    if (obj.getTipo() == "curacion") {
        int vidaAnterior = vida;
        setVida(vida + obj.getValor());
        int vidaRestaurada = vida - vidaAnterior;
        std::cout << ">>> " << nombre << " uso " << obj.getNombre() << std::endl;
        std::cout << ">>> Vida restaurada: +" << vidaRestaurada << " HP" << std::endl;
        std::cout << "Stats despues: HP=" << vida << "/" << vidaMaxima
                  << " | ATK=" << ataque << " | DEF=" << defensa << std::endl;
        inventario.erase(inventario.begin() + indice);
    } else if (obj.getTipo() == "arma") {
        ataque = ataque + obj.getValor();
        std::cout << ">>> " << nombre << " equipo " << obj.getNombre() << std::endl;
        std::cout << ">>> Ataque aumentado permanentemente: +" << obj.getValor() << std::endl;
        std::cout << "Stats despues: HP=" << vida << "/" << vidaMaxima
                  << " | ATK=" << ataque << " | DEF=" << defensa << std::endl;
        inventario.erase(inventario.begin() + indice);
    }
}

int Jugador::getNumObjetos() {
    return inventario.size();
}

void Jugador::sumarAccion(int puntos) {
    accionPuntos = accionPuntos + puntos;
}

void Jugador::sumarEmpatia(int puntos) {
    empatiaPuntos = empatiaPuntos + puntos;
}

void Jugador::sumarSacrificio(int puntos) {
    sacrificioPuntos = sacrificioPuntos + puntos;
}

int Jugador::getAccionPuntos() {
    return accionPuntos;
}

int Jugador::getEmpatiaPuntos() {
    return empatiaPuntos;
}

int Jugador::getSacrificioPuntos() {
    return sacrificioPuntos;
}