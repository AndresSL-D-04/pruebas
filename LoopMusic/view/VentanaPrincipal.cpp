#include "VentanaPrincipal.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QFont>
#include <QFileDialog>
#include <QMessageBox>
#include <QMediaDevices>
#include <QAudioDevice>

VentanaPrincipal::VentanaPrincipal(QWidget* parent) : QWidget(parent) {
    setWindowTitle("LoopMusic - Grupo 3");
    resize(1050, 700);

    player   = new QMediaPlayer(this);
    audioOut = new QAudioOutput(this);
    player->setAudioOutput(audioOut);
    audioOut->setVolume(0.8);
    audioOut->setDevice(QMediaDevices::defaultAudioOutput());

    QVBoxLayout* principal = new QVBoxLayout(this);
    principal->setSpacing(10);

    QLabel* titulo = new QLabel("LoopMusic");
    QFont f = titulo->font();
    f.setPointSize(20);
    f.setBold(true);
    titulo->setFont(f);
    titulo->setAlignment(Qt::AlignCenter);
    principal->addWidget(titulo);

    QLabel* subtitulo = new QLabel("Grupo 3 - Listas Circulares Doblemente Enlazadas");
    subtitulo->setAlignment(Qt::AlignCenter);
    subtitulo->setStyleSheet("color:#7f8c8d;font-style:italic;font-size:11px;margin-bottom:6px;");
    principal->addWidget(subtitulo);

    QGroupBox* grupoLista = new QGroupBox("Lista circular doblemente enlazada");
    QVBoxLayout* vLista = new QVBoxLayout(grupoLista);

    contenedorTarjetas = new QWidget();
    layoutTarjetas = new QHBoxLayout(contenedorTarjetas);
    layoutTarjetas->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    layoutTarjetas->setSpacing(8);

    scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setWidget(contenedorTarjetas);
    scroll->setMinimumHeight(150);
    scroll->setStyleSheet("QScrollArea{background:#ecf0f1;border:1px solid #bdc3c7;border-radius:6px;}");

    vLista->addWidget(scroll);
    principal->addWidget(grupoLista, 2);

    QGroupBox* grupoRepro = new QGroupBox("Reproduccion");
    QVBoxLayout* vRepro = new QVBoxLayout(grupoRepro);

    lblActual    = new QLabel("Actual:    (ninguna)");
    lblAnterior  = new QLabel("Anterior:  (ninguna)");
    lblSiguiente = new QLabel("Siguiente: (ninguna)");

    QFont fBold = lblActual->font();
    fBold.setBold(true);
    lblActual->setFont(fBold);
    lblActual->setStyleSheet("color:#27ae60;");

    vRepro->addWidget(lblAnterior);
    vRepro->addWidget(lblActual);
    vRepro->addWidget(lblSiguiente);

    QHBoxLayout* navLayout = new QHBoxLayout();
    btnAnterior  = new QPushButton("<< Anterior");
    btnSiguiente = new QPushButton("Siguiente >>");
    btnAnterior->setMinimumHeight(36);
    btnSiguiente->setMinimumHeight(36);
    btnAnterior->setStyleSheet("QPushButton{background:#3498db;color:white;font-weight:bold;border-radius:6px;}"
                               "QPushButton:hover{background:#2980b9;}");
    btnSiguiente->setStyleSheet("QPushButton{background:#e67e22;color:white;font-weight:bold;border-radius:6px;}"
                                "QPushButton:hover{background:#d35400;}");
    navLayout->addWidget(btnAnterior);
    navLayout->addWidget(btnSiguiente);
    vRepro->addLayout(navLayout);

    principal->addWidget(grupoRepro, 1);

    QGroupBox* grupoOps = new QGroupBox("Operaciones sobre la lista");
    QVBoxLayout* vOps = new QVBoxLayout(grupoOps);

    btnSubir = new QPushButton("Subir musica desde archivo...");
    btnSubir->setMinimumHeight(40);
    btnSubir->setStyleSheet("QPushButton{background:#8e44ad;color:white;font-weight:bold;"
                            "border-radius:8px;font-size:14px;}"
                            "QPushButton:hover{background:#713289;}");
    vOps->addWidget(btnSubir);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    edtTitulo  = new QLineEdit();
    edtArtista = new QLineEdit();
    edtTitulo->setPlaceholderText("Titulo de la cancion");
    edtArtista->setPlaceholderText("Artista");
    inputLayout->addWidget(new QLabel("Titulo:"));
    inputLayout->addWidget(edtTitulo);
    inputLayout->addWidget(new QLabel("Artista:"));
    inputLayout->addWidget(edtArtista);
    vOps->addLayout(inputLayout);

    QHBoxLayout* posLayout = new QHBoxLayout();
    spnPosicion = new QSpinBox();
    spnPosicion->setRange(0, 999);
    posLayout->addWidget(new QLabel("Posicion:"));
    posLayout->addWidget(spnPosicion);
    posLayout->addStretch();
    vOps->addLayout(posLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnInicio   = new QPushButton("+ Al inicio");
    btnFinal    = new QPushButton("+ Al final");
    btnEnPos    = new QPushButton("+ En posicion");
    btnEliminar = new QPushButton("x Eliminar");
    btnBuscar   = new QPushButton("Buscar");
    btnMostrar  = new QPushButton("Mostrar lista");
    btnVaciar   = new QPushButton("Vaciar");

    btnLayout->addWidget(btnInicio);
    btnLayout->addWidget(btnFinal);
    btnLayout->addWidget(btnEnPos);
    btnLayout->addWidget(btnEliminar);
    btnLayout->addWidget(btnBuscar);
    btnLayout->addWidget(btnMostrar);
    btnLayout->addWidget(btnVaciar);
    vOps->addLayout(btnLayout);

    principal->addWidget(grupoOps);

    lblEstado = new QLabel("Listo. 0 canciones en la lista circular.");
    lblEstado->setStyleSheet("background:#34495e;color:white;padding:6px;border-radius:4px;");
    principal->addWidget(lblEstado);
}

VentanaPrincipal::~VentanaPrincipal() {}

void VentanaPrincipal::limpiarTarjetas() {
    QLayoutItem* item;
    while ((item = layoutTarjetas->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }
}

QHBoxLayout* VentanaPrincipal::getLayoutTarjetas() {
    return layoutTarjetas;
}

QFrame* VentanaPrincipal::crearTarjeta(const QString& titulo,
                                       const QString& artista,
                                       bool tieneAudio,
                                       bool esActual,
                                       int indice) {
    QFrame* tarjeta = new QFrame();
    tarjeta->setFixedSize(160, 110);
    QString estilo = esActual
        ? "QFrame{background:#2ecc71;color:white;border-radius:10px;border:3px solid #27ae60;}"
        : "QFrame{background:#34495e;color:white;border-radius:10px;border:1px solid #2c3e50;}";
    tarjeta->setStyleSheet(estilo);

    QVBoxLayout* v = new QVBoxLayout(tarjeta);
    v->setSpacing(2);

    QLabel* lTitulo = new QLabel(titulo);
    lTitulo->setWordWrap(true);
    lTitulo->setAlignment(Qt::AlignCenter);
    lTitulo->setStyleSheet("font-weight:bold;font-size:12px;");

    QLabel* lArtista = new QLabel(artista);
    lArtista->setAlignment(Qt::AlignCenter);
    lArtista->setStyleSheet("font-size:11px;font-style:italic;");

    QLabel* lAudio = new QLabel(tieneAudio ? "[MP3]" : "[manual]");
    lAudio->setAlignment(Qt::AlignCenter);
    lAudio->setStyleSheet(tieneAudio
        ? "font-size:9px;color:#f1c40f;font-weight:bold;"
        : "font-size:9px;color:#bdc3c7;");

    QLabel* lRol = new QLabel(esActual ? "ACTUAL" : QString("Nodo %1").arg(indice));
    lRol->setAlignment(Qt::AlignCenter);
    lRol->setStyleSheet("font-size:9px;color:#ffffff;font-weight:bold;");

    v->addWidget(lTitulo);
    v->addWidget(lArtista);
    v->addWidget(lAudio);
    v->addWidget(lRol);
    return tarjeta;
}

QLabel* VentanaPrincipal::crearFlecha() {
    QLabel* flecha = new QLabel("<->");
    flecha->setStyleSheet("color:#2c3e50;font-size:18px;font-weight:bold;");
    return flecha;
}

QLabel* VentanaPrincipal::crearIndicadorCircular() {
    QLabel* circ = new QLabel("(vuelve al inicio)");
    circ->setStyleSheet("color:#e74c3c;font-weight:bold;padding-left:8px;");
    return circ;
}

QLabel* VentanaPrincipal::crearMensajeVacio() {
    QLabel* vacio = new QLabel("La lista esta vacia. Sube musica o agrega una cancion.");
    vacio->setStyleSheet("color:#7f8c8d;font-style:italic;padding:20px;");
    return vacio;
}

void VentanaPrincipal::setEtiquetas(const QString& actual,
                                    const QString& anterior,
                                    const QString& siguiente) {
    lblActual->setText(actual);
    lblAnterior->setText(anterior);
    lblSiguiente->setText(siguiente);
}

void VentanaPrincipal::setEstado(const QString& msg) {
    lblEstado->setText(msg);
}

QStringList VentanaPrincipal::pedirArchivosMusica() {
    return QFileDialog::getOpenFileNames(
        this,
        "Selecciona los archivos de musica",
        QString(),
        "Audio (*.mp3 *.wav *.ogg *.flac *.m4a);;Todos los archivos (*)"
    );
}

void VentanaPrincipal::mostrarError(const QString& msg) {
    QMessageBox::warning(this, "Operacion invalida", msg);
}

void VentanaPrincipal::mostrarInfo(const QString& msg) {
    QMessageBox::information(this, "Informacion", msg);
}

bool VentanaPrincipal::confirmar(const QString& msg) {
    return QMessageBox::question(this, "Confirmar", msg) == QMessageBox::Yes;
}

QString VentanaPrincipal::getTitulo() const {
    return edtTitulo->text().trimmed();
}

QString VentanaPrincipal::getArtista() const {
    return edtArtista->text().trimmed();
}

int VentanaPrincipal::getPosicion() const {
    return spnPosicion->value();
}

void VentanaPrincipal::limpiarEntradas() {
    edtTitulo->clear();
    edtArtista->clear();
}
