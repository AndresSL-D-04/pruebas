#ifndef CANCION_H
#define CANCION_H

#include <string>

struct Cancion {
    std::string titulo;
    std::string artista;
    std::string rutaArchivo;

    Cancion() : titulo(""), artista(""), rutaArchivo("") {}
    Cancion(std::string t, std::string a)
        : titulo(t), artista(a), rutaArchivo("") {}
    Cancion(std::string t, std::string a, std::string ruta)
        : titulo(t), artista(a), rutaArchivo(ruta) {}

    bool operator==(const Cancion& otra) const {
        return titulo == otra.titulo && artista == otra.artista
               && rutaArchivo == otra.rutaArchivo;
    }
};

#endif
