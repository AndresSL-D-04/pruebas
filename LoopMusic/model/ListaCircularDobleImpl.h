#ifndef LISTACIRCULARDOBLEIMPL_H
#define LISTACIRCULARDOBLEIMPL_H

#include "ListaCircularDoble.h"

template <typename T>
ListaCircularDoble<T>::ListaCircularDoble() {
    inicio = nullptr;
    actual = nullptr;
    tam = 0;
}

template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    vaciar();
}

template <typename T>
bool ListaCircularDoble<T>::estaVacia() const { return inicio == nullptr; }

template <typename T>
int ListaCircularDoble<T>::getTam() const { return tam; }

template <typename T>
Nodo<T>* ListaCircularDoble<T>::getInicio() const { return inicio; }

template <typename T>
Nodo<T>* ListaCircularDoble<T>::getActual() const { return actual; }

template <typename T>
void ListaCircularDoble<T>::insertarAlInicio(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (inicio == nullptr) {
        inicio = nuevo;
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        actual = inicio;
    } else {
        Nodo<T>* ultimo = inicio->getAnterior();
        nuevo->setSiguiente(inicio);
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        inicio->setAnterior(nuevo);
        inicio = nuevo;
    }
    tam++;
}

template <typename T>
void ListaCircularDoble<T>::insertarAlFinal(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (inicio == nullptr) {
        inicio = nuevo;
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        actual = inicio;
    } else {
        Nodo<T>* ultimo = inicio->getAnterior();
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(inicio);
        inicio->setAnterior(nuevo);
    }
    tam++;
}

template <typename T>
bool ListaCircularDoble<T>::insertarEnPosicion(T dato, int pos) {
    if (pos < 0 || pos > tam) return false;
    if (pos == 0) { insertarAlInicio(dato); return true; }
    if (pos == tam) { insertarAlFinal(dato); return true; }

    Nodo<T>* nuevo = new Nodo<T>(dato);
    Nodo<T>* aux = inicio;
    for (int i = 0; i < pos - 1; i++) aux = aux->getSiguiente();

    Nodo<T>* sig = aux->getSiguiente();
    nuevo->setSiguiente(sig);
    nuevo->setAnterior(aux);
    aux->setSiguiente(nuevo);
    sig->setAnterior(nuevo);
    tam++;
    return true;
}

template <typename T>
bool ListaCircularDoble<T>::eliminarPorDato(T dato) {
    if (inicio == nullptr) return false;
    Nodo<T>* aux = inicio;
    int pos = 0;
    do {
        if (aux->getDato() == dato) return eliminarEnPosicion(pos);
        aux = aux->getSiguiente();
        pos++;
    } while (aux != inicio);
    return false;
}

template <typename T>
bool ListaCircularDoble<T>::eliminarEnPosicion(int pos) {
    if (inicio == nullptr || pos < 0 || pos >= tam) return false;

    Nodo<T>* borrar = inicio;
    for (int i = 0; i < pos; i++) borrar = borrar->getSiguiente();

    if (tam == 1) {
        inicio = nullptr;
        actual = nullptr;
    } else {
        Nodo<T>* ant = borrar->getAnterior();
        Nodo<T>* sig = borrar->getSiguiente();
        ant->setSiguiente(sig);
        sig->setAnterior(ant);
        if (borrar == inicio) inicio = sig;
        if (borrar == actual) actual = sig;
    }
    delete borrar;
    tam--;
    return true;
}

template <typename T>
Nodo<T>* ListaCircularDoble<T>::buscar(T dato) const {
    if (inicio == nullptr) return nullptr;
    Nodo<T>* aux = inicio;
    do {
        if (aux->getDato() == dato) return aux;
        aux = aux->getSiguiente();
    } while (aux != inicio);
    return nullptr;
}

template <typename T>
T ListaCircularDoble<T>::obtenerActual() const {
    if (actual == nullptr) return T();
    return actual->getDato();
}

template <typename T>
T ListaCircularDoble<T>::obtenerSiguiente() const {
    if (actual == nullptr) return T();
    return actual->getSiguiente()->getDato();
}

template <typename T>
T ListaCircularDoble<T>::obtenerAnterior() const {
    if (actual == nullptr) return T();
    return actual->getAnterior()->getDato();
}

template <typename T>
void ListaCircularDoble<T>::avanzar() {
    if (actual != nullptr) actual = actual->getSiguiente();
}

template <typename T>
void ListaCircularDoble<T>::retroceder() {
    if (actual != nullptr) actual = actual->getAnterior();
}

template <typename T>
void ListaCircularDoble<T>::vaciar() {
    if (inicio == nullptr) return;
    Nodo<T>* aux = inicio;
    do {
        Nodo<T>* sig = aux->getSiguiente();
        delete aux;
        aux = sig;
    } while (aux != inicio);
    inicio = nullptr;
    actual = nullptr;
    tam = 0;
}

#endif
