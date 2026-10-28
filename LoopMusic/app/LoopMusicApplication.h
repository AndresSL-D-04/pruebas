#ifndef LOOPMUSICAPPLICATION_H
#define LOOPMUSICAPPLICATION_H

#include <QApplication>

class VentanaPrincipal;
class ReproductorController;

class LoopMusicApplication : public QApplication {
    Q_OBJECT

private:
    VentanaPrincipal*      vista;
    ReproductorController* controlador;

    void configurarAplicacion();
    void construirComponentes();

public:
    LoopMusicApplication(int& argc, char** argv);
    ~LoopMusicApplication();

    int ejecutar();
};

#endif
