#include "ReproductorController.h"
#include "Validaciones.h"

#include <QFileInfo>
#include <QUrl>
#include <QDir>

ReproductorController::ReproductorController(VentanaPrincipal* vista, QObject* parent)
    : QObject(parent), vista(vista) {
    modelo = new ListaCircularDoble<Cancion>();
    conectarEventos();
    refrescarVista();
}

ReproductorController::~ReproductorController() {
    delete modelo;
}

void ReproductorController::conectarEventos() {
    connect(vista->btnSubir,    &QPushButton::clicked, this, &ReproductorController::onSubirMusica);
    connect(vista->btnInicio,   &QPushButton::clicked, this, &ReproductorController::onAgregarInicio);
    connect(vista->btnFinal,    &QPushButton::clicked, this, &ReproductorController::onAgregarFinal);
    connect(vista->btnEnPos,    &QPushButton::clicked, this, &ReproductorController::onInsertarPosicion);
    connect(vista->btnEliminar, &QPushButton::clicked, this, &ReproductorController::onEliminar);
    connect(vista->btnBuscar,   &QPushButton::clicked, this, &ReproductorController::onBuscar);
    connect(vista->btnMostrar,  &QPushButton::clicked, this, &ReproductorController::onMostrarLista);
    connect(vista->btnVaciar,   &QPushButton::clicked, this, &ReproductorController::onVaciar);
    connect(vista->btnAnterior, &QPushButton::clicked, this, &ReproductorController::onAnterior);
    connect(vista->btnSiguiente,&QPushButton::clicked, this, &ReproductorController::onSiguiente);
}

void ReproductorController::refrescarVista() {
    vista->limpiarTarjetas();

    if (modelo->estaVacia()) {
        vista->getLayoutTarjetas()->addWidget(vista->crearMensajeVacio());
        vista->setEtiquetas("Actual:    (ninguna)",
                            "Anterior:  (ninguna)",
                            "Siguiente: (ninguna)");
        return;
    }

    Nodo<Cancion>* aux = modelo->getInicio();
    for (int i = 0; i < modelo->getTam(); i++) {
        bool esActual   = (aux == modelo->getActual());
        bool tieneAudio = !aux->getDato().rutaArchivo.empty();

        vista->getLayoutTarjetas()->addWidget(
            vista->crearTarjeta(
                QString::fromStdString(aux->getDato().titulo),
                QString::fromStdString(aux->getDato().artista),
                tieneAudio, esActual, i));

        if (i < modelo->getTam() - 1)
            vista->getLayoutTarjetas()->addWidget(vista->crearFlecha());

        aux = aux->getSiguiente();
    }
    vista->getLayoutTarjetas()->addWidget(vista->crearIndicadorCircular());

    Cancion a = modelo->obtenerActual();
    Cancion p = modelo->obtenerAnterior();
    Cancion s = modelo->obtenerSiguiente();
    vista->setEtiquetas(
        QString("Actual:    \"%1\" - %2")
            .arg(QString::fromStdString(a.titulo), QString::fromStdString(a.artista)),
        QString("Anterior:  \"%1\" - %2")
            .arg(QString::fromStdString(p.titulo), QString::fromStdString(p.artista)),
        QString("Siguiente: \"%1\" - %2")
            .arg(QString::fromStdString(s.titulo), QString::fromStdString(s.artista)));
}

void ReproductorController::reproducirActual() {
    if (modelo->estaVacia()) return;
    Cancion c = modelo->obtenerActual();

    if (c.rutaArchivo.empty()) {
        vista->player->stop();
        vista->setEstado(QString("Actual: \"%1\" - %2 (sin audio)")
                         .arg(QString::fromStdString(c.titulo),
                              QString::fromStdString(c.artista)));
        return;
    }

    QString ruta = QString::fromStdString(c.rutaArchivo);
    QString rutaNativa = QDir::toNativeSeparators(ruta);

    vista->player->setSource(QUrl::fromLocalFile(rutaNativa));
    vista->player->play();
    vista->setEstado(QString("Reproduciendo: \"%1\" - %2")
                     .arg(QString::fromStdString(c.titulo),
                          QString::fromStdString(c.artista)));
}

bool ReproductorController::datosManualesValidos(Cancion& out) {
    std::string t = vista->getTitulo().toStdString();
    std::string a = vista->getArtista().toStdString();

    if (!Validaciones::tituloValido(t)) {
        vista->mostrarError("El titulo no puede estar vacio.");
        return false;
    }
    if (!Validaciones::artistaValido(a)) {
        vista->mostrarError("El artista no puede estar vacio.");
        return false;
    }
    out = Cancion(t, a);
    return true;
}

void ReproductorController::onSubirMusica() {
    QStringList archivos = vista->pedirArchivosMusica();
    if (archivos.isEmpty()) {
        vista->setEstado("Subida cancelada.");
        return;
    }

    int agregadas = 0;
    for (int i = 0; i < archivos.size(); i++) {
        QFileInfo info(archivos.at(i));
        QString nombre = info.completeBaseName();
        QString titulo = nombre;
        QString artista = "Artista desconocido";

        int guion = nombre.indexOf(" - ");
        if (guion > 0) {
            artista = nombre.left(guion).trimmed();
            titulo  = nombre.mid(guion + 3).trimmed();
        }
        if (titulo.isEmpty()) titulo = nombre;

        modelo->insertarAlFinal(
            Cancion(titulo.toStdString(),
                    artista.toStdString(),
                    archivos.at(i).toStdString()));
        agregadas++;
    }

    refrescarVista();
    vista->setEstado(QString("Se agregaron %1 archivo(s). Total: %2")
                     .arg(agregadas).arg(modelo->getTam()));
}

void ReproductorController::onAgregarInicio() {
    Cancion c;
    if (!datosManualesValidos(c)) return;
    modelo->insertarAlInicio(c);
    refrescarVista();
    vista->limpiarEntradas();
    vista->setEstado(QString("Cancion \"%1\" insertada al inicio.")
                     .arg(QString::fromStdString(c.titulo)));
}

void ReproductorController::onAgregarFinal() {
    Cancion c;
    if (!datosManualesValidos(c)) return;
    modelo->insertarAlFinal(c);
    refrescarVista();
    vista->limpiarEntradas();
    vista->setEstado(QString("Cancion \"%1\" insertada al final.")
                     .arg(QString::fromStdString(c.titulo)));
}

void ReproductorController::onInsertarPosicion() {
    Cancion c;
    if (!datosManualesValidos(c)) return;

    int pos = vista->getPosicion();
    if (!Validaciones::posicionValida(pos, modelo->getTam())) {
        vista->mostrarError(QString("Posicion invalida (0 a %1)").arg(modelo->getTam()));
        return;
    }
    modelo->insertarEnPosicion(c, pos);
    refrescarVista();
    vista->limpiarEntradas();
    vista->setEstado(QString("Cancion \"%1\" insertada en posicion %2.")
                     .arg(QString::fromStdString(c.titulo)).arg(pos));
}

void ReproductorController::onEliminar() {
    if (modelo->estaVacia()) {
        vista->mostrarError("La lista esta vacia.");
        return;
    }
    int pos = vista->getPosicion();
    if (pos < 0 || pos >= modelo->getTam()) {
        vista->mostrarError(QString("Posicion invalida (0 a %1)").arg(modelo->getTam() - 1));
        return;
    }
    if (modelo->eliminarEnPosicion(pos)) {
        refrescarVista();
        vista->setEstado(QString("Cancion eliminada en posicion %1.").arg(pos));
    } else {
        vista->mostrarError("No se pudo eliminar.");
    }
}

void ReproductorController::onSiguiente() {
    if (modelo->estaVacia()) {
        vista->mostrarError("La lista esta vacia.");
        return;
    }
    modelo->avanzar();
    refrescarVista();
    reproducirActual();
}

void ReproductorController::onAnterior() {
    if (modelo->estaVacia()) {
        vista->mostrarError("La lista esta vacia.");
        return;
    }
    modelo->retroceder();
    refrescarVista();
    reproducirActual();
}

void ReproductorController::onBuscar() {
    if (modelo->estaVacia()) {
        vista->mostrarError("La lista esta vacia.");
        return;
    }
    QString t = vista->getTitulo();
    if (t.isEmpty()) {
        vista->mostrarError("Ingresa un titulo.");
        return;
    }

    Nodo<Cancion>* encontrado = nullptr;
    Nodo<Cancion>* aux = modelo->getInicio();
    do {
        if (QString::fromStdString(aux->getDato().titulo) == t) {
            encontrado = aux;
            break;
        }
        aux = aux->getSiguiente();
    } while (aux != modelo->getInicio());

    if (encontrado) {
        vista->mostrarInfo(QString("Encontrada:\n\"%1\" - %2\nArchivo: %3")
                           .arg(QString::fromStdString(encontrado->getDato().titulo),
                                QString::fromStdString(encontrado->getDato().artista),
                                QString::fromStdString(encontrado->getDato().rutaArchivo)));
    } else {
        vista->mostrarError(QString("No se encontro \"%1\".").arg(t));
    }
}

void ReproductorController::onMostrarLista() {
    if (modelo->estaVacia()) {
        vista->mostrarError("La lista esta vacia.");
        return;
    }
    QString txt = "Lista circular:\n\n";
    Nodo<Cancion>* aux = modelo->getInicio();
    int i = 0;
    do {
        QString marca = (aux == modelo->getActual()) ? " <-- ACTUAL" : "";
        QString audio = aux->getDato().rutaArchivo.empty() ? "[manual]" : "[archivo]";
        txt += QString("[%1] \"%2\" - %3 %4%5\n")
               .arg(i++)
               .arg(QString::fromStdString(aux->getDato().titulo),
                    QString::fromStdString(aux->getDato().artista),
                    audio, marca);
        aux = aux->getSiguiente();
    } while (aux != modelo->getInicio());
    txt += "\nDespues del ultimo vuelve al primero.";
    vista->mostrarInfo(txt);
}

void ReproductorController::onVaciar() {
    if (modelo->estaVacia()) {
        vista->mostrarError("La lista ya esta vacia.");
        return;
    }
    if (!vista->confirmar("Vaciar toda la lista?")) return;

    vista->player->stop();
    modelo->vaciar();
    refrescarVista();
    vista->setEstado("Lista vaciada. Memoria liberada.");
}
