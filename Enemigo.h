#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <string>
#include "Entidad.h"

class Enemigo : public Entidad {
private:
    std::string tipo;

public:
    Enemigo(std::string nombre, std::string tipo, int vida, int ataque, int defensa);

    void atacar(Entidad* objetivo) override;
    void mostrarEstado() override;
    std::string getTipo();
};

#endif