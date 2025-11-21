#include "Juego.h"
#include "Jugador.h"
#include "Enemigo.h"
#include "Habitacion.h"
#include "Objeto.h"
#include <iostream>
#include <vector>
#include <string>

Juego::Juego() {
    jugador = new Jugador("Bunzu");
    juegoActivo = true;
    crearMundo();
}

Juego::~Juego() {
    delete jugador;
    for (size_t i = 0; i < habitaciones.size(); i++) {
        delete habitaciones[i];
    }
}

void Juego::crearMundo() {
    // Crear habitaciones con mejor descripcion
    Habitacion* madriguera = new Habitacion("La Madriguera",
        "Tu hogar. Todo parece normal, pero...\nHumo negro y purpura se eleva a lo lejos desde la aldea.");

    Habitacion* aldea = new Habitacion("Aldea en Caos",
        "Casas ardiendo. Conejos corriendo asustados.\nRaices negras emergen del suelo.");

    Habitacion* templo = new Habitacion("El Templo de Zuri",
        "Un lugar sagrado y pacifico.\nZuri, la anciana guardian, medita frente a un cristal antiguo.");

    Habitacion* bosque = new Habitacion("Bosque Herido",
        "Los arboles lloran savia negra. El aire es pesado.\nUna raiz gigante bloquea el camino.");

    Habitacion* castillo = new Habitacion("Castillo de Raices",
        "El corazon de la oscuridad.\nRaices gigantes forman un castillo viviente.\nKarothar te espera.");

    // Conectar de forma lineal
    madriguera->conectarSalida(0, aldea);
    aldea->conectarSalida(1, madriguera);
    aldea->conectarSalida(2, templo);
    templo->conectarSalida(3, aldea);
    templo->conectarSalida(0, bosque);
    bosque->conectarSalida(1, templo);
    bosque->conectarSalida(0, castillo);
    castillo->conectarSalida(1, bosque);

    // Agregar enemigos
    aldea->agregarEnemigo(new Enemigo("Mini-Zanahoria Corrupta", "Mini-Zanahoria", 30, 8, 2));
    aldea->agregarEnemigo(new Enemigo("Mini-Zanahoria Oscura", "Mini-Zanahoria", 30, 8, 2));

    bosque->agregarEnemigo(new Enemigo("Raiz Guardiana", "Boss", 100, 12, 5));

    castillo->agregarEnemigo(new Enemigo("Karothar - Zanahoria Primordial", "Jefe Final", 150, 18, 8));

    // Agregar objetos en lugares clave
    madriguera->agregarObjeto(Objeto("Pocion de Vida", "curacion", 30));
    templo->agregarObjeto(Objeto("Miel Curativa de Zuri", "curacion", 50));
    templo->agregarObjeto(Objeto("Espada de Luz", "arma", 10));

    // Guardar habitaciones
    habitaciones.push_back(madriguera);
    habitaciones.push_back(aldea);
    habitaciones.push_back(templo);
    habitaciones.push_back(bosque);
    habitaciones.push_back(castillo);

    habitacionActual = madriguera;
}

void Juego::iniciar() {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "  BUNNY WARRIORS: LAS AVENTURAS DE BUNZU" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "\n--- PROLOGO: EL ECLIPSE CARMESI ---\n" << std::endl;

    std::cout << "En el Bosque Esmeralda, donde las zanahorias crecian dulces," << std::endl;
    std::cout << "una oscuridad ancestral desperto..." << std::endl;
    std::cout << "\nHace mil anios, Karothar - la Zanahoria Primordial - fue sellada." << std::endl;
    std::cout << "Pero los sellos se debilitan." << std::endl;

    std::cout << "\nUna voz susurra en tus suenios:" << std::endl;
    std::cout << "\"Despierta... mil anios de hambre...\"" << std::endl;

    std::cout << "\n\nPresiona Enter para despertar...";
    std::cin.ignore();
    std::cin.get();

    std::cout << "\n\n--- CAPITULO 1: EL DESPERTAR ---\n" << std::endl;
    std::cout << "Despiertas sobresaltado." << std::endl;
    std::cout << "Ese suenio otra vez... algo no esta bien." << std::endl;
    std::cout << "\nMiras por la ventana de tu madriguera." << std::endl;
    std::cout << "Humo negro y purpura se eleva desde la aldea." << std::endl;

    std::cout << "\n\nQUE HACES?" << std::endl;
    std::cout << "1. Correr hacia el humo (Ruta Accion)" << std::endl;
    std::cout << "2. Buscar ayuda en el Templo primero (Ruta Empatia)" << std::endl;
    std::cout << "3. Comer y prepararte antes de salir (Ruta Sacrificio)" << std::endl;
    std::cout << "\nElige (1-3): ";

    int decision;

    // Validar entrada para evitar crashes
    if (!(std::cin >> decision)) {
        // Si la entrada no es un numero, limpiar el buffer
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        decision = 1; // Valor por defecto
        std::cout << "\nEntrada no valida. Se selecciona opcion 1 por defecto." << std::endl;
    }

    if (decision == 1) {
        std::cout << "\nCorres sin pensar hacia el peligro." << std::endl;
        std::cout << "Tu corazon late fuerte. Tienes que ayudar." << std::endl;
        jugador->sumarAccion(2);
        std::cout << "\n[+2 Puntos de Accion]" << std::endl;
    } else if (decision == 2) {
        std::cout << "\nLa sabiduria esta en buscar consejo primero." << std::endl;
        std::cout << "El Templo tiene respuestas. Zuri puede ayudar." << std::endl;
        jugador->sumarEmpatia(2);
        std::cout << "\n[+2 Puntos de Empatia]" << std::endl;

        // Aumentar vida maxima permanentemente y curar completamente
        int vidaMaxAnterior = jugador->getVidaMaxima();
        jugador->setVidaMaxima(vidaMaxAnterior + 20);
        jugador->setVida(jugador->getVidaMaxima()); // Curar al maximo
        std::cout << "\nRecibes bendicion de Zuri: +20 HP maximo y curacion completa" << std::endl;
        std::cout << "Vida: " << jugador->getVida() << "/" << jugador->getVidaMaxima() << " HP" << std::endl;
    } else if (decision == 3) {
        std::cout << "\n\"Sin energia, no puedo ayudar a nadie\"" << std::endl;
        std::cout << "Comes rapido pero con calma. Tu cuerpo lo agradece." << std::endl;
        jugador->sumarSacrificio(2);
        std::cout << "\n[+2 Puntos de Sacrificio]" << std::endl;

        int vidaAnterior = jugador->getVida();
        jugador->setVida(jugador->getVida() + 15);
        int vidaCurada = jugador->getVida() - vidaAnterior;
        std::cout << "Te sientes mas fuerte: +" << vidaCurada << " HP (Vida: " << jugador->getVida() << "/" << jugador->getVidaMaxima() << ")" << std::endl;
    }

    std::cout << "\n\nSales de tu madriguera hacia lo desconocido..." << std::endl;
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Juego::combate() {
    std::vector<Enemigo*>& enemigos = habitacionActual->getEnemigos();

    std::cout << "\n========================================" << std::endl;
    std::cout << "           COMBATE!" << std::endl;
    std::cout << "========================================" << std::endl;

    // Dialogo especial segun ubicacion
    if (habitacionActual->getNombre() == "Aldea en Caos") {
        std::cout << "\nLas Mini-Zanahorias atacan a los aldeanos!" << std::endl;
        std::cout << "Una de ellas susurra: \"Hambre... como el... siempre hambre...\"" << std::endl;
        std::cout << "\nNo son solo monstruos. Es... dolor cristalizado." << std::endl;
    } else if (habitacionActual->getNombre() == "Bosque Herido") {
        std::cout << "\nUna raiz gigante bloquea el camino." << std::endl;
        std::cout << "Durante la pelea, la raiz sangra savia..." << std::endl;
        std::cout << "Y pequenias flores rojas brotan del suelo." << std::endl;
        std::cout << "\nIncluso la corrupcion recuerda la vida. Esa es la tragedia." << std::endl;
    } else if (habitacionActual->getNombre() == "Castillo de Raices") {
        std::cout << "\nKarothar: \"Llegaste. Bien.\"" << std::endl;
        std::cout << "Bunzu: \"No tiene que ser asi.\"" << std::endl;
        std::cout << "Karothar: \"Entonces dime, guardian. Como DEBERIA ser?\"" << std::endl;
        std::cout << "\nLa batalla final comienza..." << std::endl;
    }

    std::cout << "\nPresiona Enter para comenzar...";
    std::cin.ignore();
    std::cin.get();

    // Variables de defensa FUERA del bucle para que persistan entre turnos
    bool estaDefendiendo = false;
    int defensaOriginal = 0;

    while (jugador->estaVivo() && enemigos.size() > 0) {
        std::cout << "\n============================================" << std::endl;
        std::cout << "                 TU TURNO                   " << std::endl;
        std::cout << "============================================" << std::endl;

        // Mostrar stats completos del jugador
        std::cout << "[" << jugador->getNombre() << "]" << std::endl;
        std::cout << "HP: " << jugador->getVida() << "/" << jugador->getVidaMaxima()
                  << " | ATK: " << jugador->getAtaque()
                  << " | DEF: " << jugador->getDefensa() << std::endl;

        std::cout << "\n--- ENEMIGOS ---" << std::endl;
        for (size_t i = 0; i < enemigos.size(); i++) {
            std::cout << i + 1 << ". ";
            enemigos[i]->mostrarEstado();
        }

        std::cout << "\n--- ACCIONES DISPONIBLES ---" << std::endl;
        std::cout << "1. Atacar (Danio base: " << jugador->getAtaque() << ")" << std::endl;
        std::cout << "2. Usar objeto (" << jugador->getNumObjetos() << " disponibles)" << std::endl;
        std::cout << "3. Defender (+10 DEF este turno)" << std::endl;
        std::cout << "\nElige (1-3): ";

        int accion;

        // Validar entrada para evitar crashes
        if (!(std::cin >> accion)) {
            // Si la entrada no es un numero, limpiar el buffer
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\nEntrada no valida. Se selecciona atacar por defecto." << std::endl;
            accion = 1;
        }

        // Restaurar defensa si se defendio en el turno anterior
        if (estaDefendiendo) {
            jugador->setDefensa(defensaOriginal);
            estaDefendiendo = false;
            std::cout << "[Defensa restaurada a valor normal]" << std::endl;
        }

        if (accion == 1) {
            if (enemigos.size() == 1) {
                std::cout << "\nAtacas a " << enemigos[0]->getNombre() << "!" << std::endl;
                jugador->atacar(enemigos[0]);

                if (!enemigos[0]->estaVivo()) {
                    std::cout << "\n" << enemigos[0]->getNombre() << " ha sido derrotado!" << std::endl;

                    if (enemigos[0]->getTipo() == "Mini-Zanahoria") {
                        std::cout << "\nAntes de desvanecerse, susurra: \"Siempre... hambre...\"" << std::endl;
                        jugador->sumarAccion(2);
                        std::cout << "[+2 Puntos de Accion]" << std::endl;
                    } else if (enemigos[0]->getTipo() == "Boss") {
                        std::cout << "\nLa raiz se desintegra en flores rojas." << std::endl;
                        std::cout << "El camino esta libre." << std::endl;
                        jugador->sumarAccion(5);
                        std::cout << "[+5 Puntos de Accion]" << std::endl;
                    } else if (enemigos[0]->getTipo() == "Jefe Final") {
                        std::cout << "\nKarothar cae..." << std::endl;
                    }

                    delete enemigos[0];
                    enemigos.erase(enemigos.begin());
                }
            } else {
                std::cout << "\nA quien atacar? (1-" << enemigos.size() << "): ";
                int objetivo;

                // Validar entrada para evitar crashes
                if (!(std::cin >> objetivo)) {
                    // Si la entrada no es un numero, limpiar el buffer
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "\nEntrada no valida. Atacando al primer enemigo." << std::endl;
                    objetivo = 1;
                }

                objetivo = objetivo - 1;

                if (objetivo >= 0 && objetivo < static_cast<int>(enemigos.size())) {
                    jugador->atacar(enemigos[objetivo]);

                    if (!enemigos[objetivo]->estaVivo()) {
                        std::cout << "\n" << enemigos[objetivo]->getNombre() << " ha sido derrotado!" << std::endl;
                        jugador->sumarAccion(2);
                        std::cout << "[+2 Puntos de Accion]" << std::endl;
                        delete enemigos[objetivo];
                        enemigos.erase(enemigos.begin() + objetivo);
                    }
                }
            }
        } else if (accion == 2) {
            jugador->mostrarInventario();
            if (jugador->getNumObjetos() > 0) {
                std::cout << "\nQue objeto usar? (0 para cancelar): ";
                int obj;

                // Validar entrada para evitar crashes
                if (!(std::cin >> obj)) {
                    // Si la entrada no es un numero, limpiar el buffer
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "\nEntrada no valida. Cancelando uso de objeto." << std::endl;
                    obj = 0;
                }

                if (obj > 0) {
                    jugador->usarObjeto(obj - 1);
                }
            } else {
                std::cout << "\nNo tienes objetos." << std::endl;
            }
        } else if (accion == 3) {
            std::cout << "\nTe preparas para defenderte." << std::endl;
            std::cout << "\"Si no cuido la vida... nadie merece estar solo.\"" << std::endl;
            jugador->sumarSacrificio(1);

            estaDefendiendo = true;
            defensaOriginal = jugador->getDefensa();
            jugador->setDefensa(defensaOriginal + 10);
            std::cout << "[Defensa +10 este turno]" << std::endl;
        }

        // Turno de enemigos
        if (enemigos.size() > 0) {
            std::cout << "\n--- Turno de enemigos ---" << std::endl;
            for (size_t i = 0; i < enemigos.size(); i++) {
                if (enemigos[i]->estaVivo()) {
                    enemigos[i]->atacar(jugador);
                }
            }
        }

        if (!jugador->estaVivo()) {
            std::cout << "\n========================================" << std::endl;
            std::cout << "         HAS SIDO DERROTADO" << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << "\nLa oscuridad te consume..." << std::endl;
            std::cout << "El bosque queda en ruinas." << std::endl;
            juegoActivo = false;
            return;
        }

        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }

    if (enemigos.size() == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "           VICTORIA!" << std::endl;
        std::cout << "========================================" << std::endl;

        if (habitacionActual->getNombre() == "Aldea en Caos") {
            std::cout << "\nLos aldeanos estan a salvo." << std::endl;
            std::cout << "Pero esto apenas comienza..." << std::endl;
        } else if (habitacionActual->getNombre() == "Bosque Herido") {
            std::cout << "\nEl camino al Castillo esta abierto." << std::endl;
            std::cout << "Sientes una presencia poderosa mas adelante." << std::endl;
        }
    }
}

void Juego::moverJugador(int direccion) {
    Habitacion* nuevaHabitacion = habitacionActual->getSalida(direccion);

    if (nuevaHabitacion != nullptr) {
        std::cout << "\n============================================" << std::endl;
        std::cout << "              MOVIMIENTO                    " << std::endl;
        std::cout << "============================================" << std::endl;
        habitacionActual = nuevaHabitacion;
        std::cout << "Te mueves a: " << habitacionActual->getNombre() << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "TUS STATS ACTUALES:" << std::endl;
        std::cout << "HP: " << jugador->getVida() << "/" << jugador->getVidaMaxima()
                  << " | ATK: " << jugador->getAtaque()
                  << " | DEF: " << jugador->getDefensa() << std::endl;
        std::cout << "============================================" << std::endl;

        habitacionActual->mostrarInfo();

        // Narrativa especial por ubicacion
        if (habitacionActual->getNombre() == "Aldea en Caos") {
            std::cout << "\nClover (aldeano): \"AYUDA! Las zanahorias atacan!\"" << std::endl;
        } else if (habitacionActual->getNombre() == "El Templo de Zuri") {
            std::cout << "\nZuri: \"Llegas justo a tiempo, Bunzu.\"" << std::endl;
            std::cout << "Zuri: \"Karothar... la Zanahoria Primordial ha despertado.\"" << std::endl;
            std::cout << "Zuri: \"Vi como la traicionaron hace mil anios. Y falle en prevenir su despertar.\"" << std::endl;
        } else if (habitacionActual->getNombre() == "Bosque Herido") {
            std::cout << "\nSientes una presencia oscura y antigua." << std::endl;
            std::cout << "Las flores rojas crecen donde cae la savia negra." << std::endl;
        } else if (habitacionActual->getNombre() == "Castillo de Raices") {
            std::cout << "\nEste es el lugar. El corazon de la oscuridad." << std::endl;
            std::cout << "Una voz resuena: \"Finalmente... alguien llega...\"" << std::endl;
        }

        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();

        // Si hay enemigos, iniciar combate
        if (habitacionActual->tieneEnemigos()) {
            combate();
        }
    } else {
        std::cout << "\nNo puedes ir en esa direccion." << std::endl;
        std::cout << "Mira bien las salidas disponibles." << std::endl;
    }
}

void Juego::recogerObjetos() {
    std::vector<Objeto>& objetos = habitacionActual->getObjetos();

    if (objetos.size() == 0) {
        std::cout << "No hay objetos aqui." << std::endl;
        return;
    }

    std::cout << "\nObjetos disponibles:" << std::endl;
    for (size_t i = 0; i < objetos.size(); i++) {
        std::cout << i + 1 << ". ";
        objetos[i].mostrarInfo();
    }

    std::cout << "Que objeto recoger? (0 para cancelar): ";
    int obj;

    // Validar entrada para evitar crashes
    if (!(std::cin >> obj)) {
        // Si la entrada no es un numero, limpiar el buffer
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Entrada no valida. Debes ingresar un numero." << std::endl;
        return;
    }

    if (obj > 0 && obj <= static_cast<int>(objetos.size())) {
        jugador->agregarObjeto(objetos[obj - 1]);
        objetos.erase(objetos.begin() + (obj - 1));
    }
}

void Juego::mostrarMenu() {
    std::cout << "\n============================================" << std::endl;
    std::cout << "          MENU PRINCIPAL                   " << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Ubicacion: " << habitacionActual->getNombre() << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "STATS DE " << jugador->getNombre() << ":" << std::endl;
    std::cout << "HP: " << jugador->getVida() << "/" << jugador->getVidaMaxima()
              << " | ATK: " << jugador->getAtaque()
              << " | DEF: " << jugador->getDefensa() << std::endl;
    std::cout << "Accion: " << jugador->getAccionPuntos()
              << " | Empatia: " << jugador->getEmpatiaPuntos()
              << " | Sacrificio: " << jugador->getSacrificioPuntos() << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\nQUE HACER?" << std::endl;
    std::cout << "1. Ver estado completo" << std::endl;
    std::cout << "2. Ver inventario" << std::endl;
    std::cout << "3. Examinar alrededor" << std::endl;
    std::cout << "4. Avanzar al Norte" << std::endl;
    std::cout << "5. Regresar al Sur" << std::endl;
    std::cout << "6. Ir al Este" << std::endl;
    std::cout << "7. Ir al Oeste" << std::endl;
    std::cout << "8. Recoger objetos" << std::endl;
    std::cout << "9. Salir del juego" << std::endl;
    std::cout << "\nOpcion (1-9): ";
}

void Juego::ejecutar() {
    while (juegoActivo) {
        // Verificar victoria
        if (habitacionActual->getNombre() == "Castillo de Raices" &&
            habitacionActual->getEnemigos().size() == 0) {

            std::cout << "\n\n========================================" << std::endl;
            std::cout << "     HAS DERROTADO A KAROTHAR" << std::endl;
            std::cout << "========================================" << std::endl;

            std::cout << "\nKarothar cae de rodillas." << std::endl;
            std::cout << "El corazon purpura empieza a brillar dorado..." << std::endl;

            std::cout << "\nKarothar (voz quebrada): \"Lloro... por primera vez en mil anios...\"" << std::endl;
            std::cout << "Karothar: \"Mi primer recuerdo... era dulce. Era... miel?\"" << std::endl;

            std::cout << "\nBunzu: \"Si. Era miel. Y puedes volver a sentirlo.\"" << std::endl;

            std::cout << "\nEl corazon se purifica completamente." << std::endl;
            std::cout << "Karothar se transforma en una pequenia zanahoria dorada." << std::endl;

            std::cout << "\nKarothar (susurrando): \"Gracias... por ver en mi lo que habia olvidado...\"" << std::endl;

            std::cout << "\n\n--- EPILOGO: 5 ANIOS DESPUES ---" << std::endl;
            std::cout << "\nEl bosque florece como nunca." << std::endl;
            std::cout << "Bunzu y Karothar son co-guardianes." << std::endl;
            std::cout << "\nClover (ahora adolescente): \"Tio Karothar! Mira lo que cultive!\"" << std::endl;
            std::cout << "Karothar (riendo): \"Hermoso. Como los viejos tiempos.\"" << std::endl;

            std::cout << "\nBunzu (sonriendo): \"La familia crece.\"" << std::endl;
            std::cout << "Zuri: \"Hiciste lo que los antiguos Guardianes no pudieron.\"" << std::endl;
            std::cout << "        \"Sanaste el corazon del bosque.\"" << std::endl;

            std::cout << "\nBunzu: \"No fui solo yo. Fuimos todos.\"" << std::endl;

            std::cout << "\n\n========================================" << std::endl;
            std::cout << "         FINAL VERDADERO" << std::endl;
            std::cout << "========================================" << std::endl;

            std::cout << "\nESTADISTICAS FINALES:" << std::endl;
            jugador->mostrarEstado();

            if (jugador->getEmpatiaPuntos() >= jugador->getAccionPuntos() &&
                jugador->getEmpatiaPuntos() >= jugador->getSacrificioPuntos()) {
                std::cout << "\nCAMINO RECORRIDO: Ruta de la Empatia" << std::endl;
                std::cout << "Entendiste que comprender es mas poderoso que destruir." << std::endl;
            } else if (jugador->getAccionPuntos() >= jugador->getEmpatiaPuntos() &&
                       jugador->getAccionPuntos() >= jugador->getSacrificioPuntos()) {
                std::cout << "\nCAMINO RECORRIDO: Ruta de la Accion" << std::endl;
                std::cout << "Tu valentia protegio a los que amas." << std::endl;
            } else {
                std::cout << "\nCAMINO RECORRIDO: Ruta del Sacrificio" << std::endl;
                std::cout << "Tu sacrificio permitio que otros vivieran." << std::endl;
            }

            std::cout << "\n\nGracias por jugar BUNNY WARRIORS" << std::endl;
            std::cout << "Guion por: RaLa (Rafa & Lau)" << std::endl;
            juegoActivo = false;
            return;
        }

        mostrarMenu();

        int opcion;

        // Validar entrada para evitar crashes
        if (!(std::cin >> opcion)) {
            // Si la entrada no es un numero, limpiar el buffer
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\nEntrada no valida. Debes ingresar un numero del 1 al 9." << std::endl;
            continue;
        }

        if (opcion == 1) {
            jugador->mostrarEstado();
        } else if (opcion == 2) {
            jugador->mostrarInventario();
        } else if (opcion == 3) {
            habitacionActual->mostrarInfo();
        } else if (opcion == 4) {
            moverJugador(0); // Norte
        } else if (opcion == 5) {
            moverJugador(1); // Sur
        } else if (opcion == 6) {
            moverJugador(2); // Este
        } else if (opcion == 7) {
            moverJugador(3); // Oeste
        } else if (opcion == 8) {
            recogerObjetos();
        } else if (opcion == 9) {
            std::cout << "\nGracias por jugar Bunny Warriors!" << std::endl;
            juegoActivo = false;
        } else {
            std::cout << "\nOpcion no valida. Elige entre 1 y 9." << std::endl;
        }
    }
}