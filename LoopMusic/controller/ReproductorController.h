#ifndef REPRODUCTORCONTROLLER_H
#define REPRODUCTORCONTROLLER_H

#include <QObject>
#include "VentanaPrincipal.h"
#include "ListaCircularDoble.h"
#include "Cancion.h"

class ReproductorController : public QObject {
    Q_OBJECT

private:
    VentanaPrincipal*            vista;
    ListaCircularDoble<Cancion>* modelo;

    void conectarEventos();
    void refrescarVista();
    void reproducirActual();
    bool datosManualesValidos(Cancion& out);

private slots:
    void onSubirMusica();
    void onAgregarInicio();
    void onAgregarFinal();
    void onInsertarPosicion();
    void onEliminar();
    void onSiguiente();
    void onAnterior();
    void onBuscar();
    void onMostrarLista();
    void onVaciar();

public:
    explicit ReproductorController(VentanaPrincipal* vista, QObject* parent = nullptr);
    ~ReproductorController();

    ListaCircularDoble<Cancion>* getModelo() const { return modelo; }
};

#endif
