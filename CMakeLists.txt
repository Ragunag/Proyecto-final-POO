cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto (debe coincidir con el nombre en CLion)
project(Proyecto_final_P00)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Archivos fuente
set(SOURCES
        main.cpp
        Entidad.cpp
        Enemigo.cpp
        Jugador.cpp
        Objeto.cpp
        Habitacion.cpp
        Juego.cpp
)

# Archivos de cabecera
set(HEADERS
        Entidad.h
        Enemigo.h
        Jugador.h
        Objeto.h
        Habitacion.h
        Juego.h
)

# Crear el ejecutable con el nombre del proyecto
add_executable(Proyecto_final_POO ${SOURCES} ${HEADERS})

# Opcional: Habilitar warnings
if(MSVC)
    target_compile_options(Proyecto_final_POO PRIVATE /W4)
else()
    target_compile_options(Proyecto_final_POO PRIVATE -Wall -Wextra -Wpedantic)
endif()