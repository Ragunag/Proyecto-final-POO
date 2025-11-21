#ifndef HABITACION_H
#define HABITACION_H

#include <string>
#include <vector>
#include "Enemigo.h"
#include "Objeto.h"

class Habitacion {
private:
    std::string nombre;
    std::string descripcion;
    std::vector<Enemigo*> enemigos;
    std::vector<Objeto> objetos;
    Habitacion* salidas[4]; // Norte, Sur, Este, Oeste

public:
    Habitacion(std::string nombre, std::string descripcion);
    ~Habitacion();

    void agregarEnemigo(Enemigo* enemigo);
    void agregarObjeto(Objeto objeto);
    void conectarSalida(int direccion, Habitacion* habitacion);

    std::string getNombre();
    std::string getDescripcion();
    void mostrarInfo();
    bool tieneEnemigos();
    std::vector<Enemigo*>& getEnemigos();
    std::vector<Objeto>& getObjetos();
    Habitacion* getSalida(int direccion);
};

#endif