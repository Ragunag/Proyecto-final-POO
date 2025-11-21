#ifndef OBJETO_H
#define OBJETO_H

#include <string>

class Objeto {
private:
    std::string nombre;
    std::string tipo;
    int valor;

public:
    Objeto(std::string nombre, std::string tipo, int valor);

    std::string getNombre();
    std::string getTipo();
    int getValor();
    void mostrarInfo();
};

#endif