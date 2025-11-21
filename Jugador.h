#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"
#include "Objeto.h"
#include <vector>

class Jugador : public Entidad {
private:
    std::vector<Objeto> inventario;
    int accionPuntos;
    int empatiaPuntos;
    int sacrificioPuntos;

public:
    Jugador(std::string nombre);

    void atacar(Entidad* objetivo) override;
    void mostrarEstado() override;

    void agregarObjeto(Objeto objeto);
    void mostrarInventario();
    void usarObjeto(int indice);
    int getNumObjetos();

    void sumarAccion(int puntos);
    void sumarEmpatia(int puntos);
    void sumarSacrificio(int puntos);

    int getAccionPuntos();
    int getEmpatiaPuntos();
    int getSacrificioPuntos();
};

#endif