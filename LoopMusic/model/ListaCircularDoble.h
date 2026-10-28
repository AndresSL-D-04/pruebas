#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include "Nodo.h"

template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* inicio;
    Nodo<T>* actual;
    int tam;

public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    bool estaVacia() const;
    int getTam() const;
    Nodo<T>* getInicio() const;
    Nodo<T>* getActual() const;

    void insertarAlInicio(T dato);
    void insertarAlFinal(T dato);
    bool insertarEnPosicion(T dato, int pos);

    bool eliminarPorDato(T dato);
    bool eliminarEnPosicion(int pos);

    Nodo<T>* buscar(T dato) const;

    T obtenerActual() const;
    T obtenerSiguiente() const;
    T obtenerAnterior() const;

    void avanzar();
    void retroceder();

    void vaciar();
};

#include "ListaCircularDobleImpl.h"
#endif
