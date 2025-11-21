#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <string>

class Entidad {
protected:
    std::string nombre;
    int vida;
    int vidaMaxima;
    int ataque;
    int defensa;

public:
    Entidad(std::string nombre, int vida, int ataque, int defensa);
    virtual ~Entidad();

    // Metodos virtuales puros (abstractos)
    virtual void atacar(Entidad* objetivo) = 0;
    virtual void mostrarEstado() = 0;

    // Getters y setters
    std::string getNombre();
    int getVida();
    int getVidaMaxima();
    int getAtaque();
    int getDefensa();
    void setVida(int nuevaVida);
    void setVidaMaxima(int nuevaVidaMax);
    void setDefensa(int nuevaDefensa);
    void recibirDanio(int danio);
    bool estaVivo();
};

#endif