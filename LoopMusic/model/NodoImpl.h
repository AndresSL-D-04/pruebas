#ifndef NODOIMPL_H
#define NODOIMPL_H

#include "Nodo.h"

template <typename T>
Nodo<T>::Nodo(T dato) {
    this->dato = dato;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

template <typename T>
Nodo<T>::~Nodo() {}

template <typename T>
T Nodo<T>::getDato() const { return dato; }

template <typename T>
void Nodo<T>::setDato(T dato) { this->dato = dato; }

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente() const { return siguiente; }

template <typename T>
void Nodo<T>::setSiguiente(Nodo<T>* sig) { siguiente = sig; }

template <typename T>
Nodo<T>* Nodo<T>::getAnterior() const { return anterior; }

template <typename T>
void Nodo<T>::setAnterior(Nodo<T>* ant) { anterior = ant; }

#endif
