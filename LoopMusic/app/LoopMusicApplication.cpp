#include "LoopMusicApplication.h"
#include "VentanaPrincipal.h"
#include "ReproductorController.h"
#include <QByteArray>

LoopMusicApplication::LoopMusicApplication(int& argc, char** argv)
    : QApplication(argc, argv) {
    configurarAplicacion();
    construirComponentes();
}

LoopMusicApplication::~LoopMusicApplication() {
    delete controlador;
    delete vista;
}

void LoopMusicApplication::configurarAplicacion() {
    setApplicationName("LoopMusic");
    setApplicationDisplayName("LoopMusic - Grupo 3");
    setOrganizationName("Grupo 3");
    setApplicationVersion("1.0.0");
}

void LoopMusicApplication::construirComponentes() {
    vista = new VentanaPrincipal();
    controlador = new ReproductorController(vista, this);
    vista->show();
}

int LoopMusicApplication::ejecutar() {
    return exec();
}

int main(int argc, char *argv[]) {
    qputenv("QT_MEDIA_BACKEND", "directshow");
    qputenv("QT_MULTIMEDIA_PREFERRED_PLUGINS", "directshow");

    LoopMusicApplication app(argc, argv);
    return app.ejecutar();
}
