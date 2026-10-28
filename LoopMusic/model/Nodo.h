#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

public:
    Nodo(T dato);
    ~Nodo();

    T getDato() const;
    void setDato(T dato);

    Nodo<T>* getSiguiente() const;
    void setSiguiente(Nodo<T>* sig);

    Nodo<T>* getAnterior() const;
    void setAnterior(Nodo<T>* ant);
};

#include "NodoImpl.h"
#endif
