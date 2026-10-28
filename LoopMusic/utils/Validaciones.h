#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    static bool tituloValido(const std::string& titulo) {
        if (titulo.empty()) return false;
        for (size_t i = 0; i < titulo.size(); i++)
            if (titulo[i] != ' ') return true;
        return false;
    }

    static bool artistaValido(const std::string& artista) {
        if (artista.empty()) return false;
        for (size_t i = 0; i < artista.size(); i++)
            if (artista[i] != ' ') return true;
        return false;
    }

    static bool posicionValida(int pos, int tam) {
        return pos >= 0 && pos <= tam;
    }
};

#endif
