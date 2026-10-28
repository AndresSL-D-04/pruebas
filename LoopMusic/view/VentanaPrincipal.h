#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStringList>

class VentanaPrincipal : public QWidget {
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget* parent = nullptr);
    ~VentanaPrincipal();

    QPushButton* btnSubir;
    QPushButton* btnInicio;
    QPushButton* btnFinal;
    QPushButton* btnEnPos;
    QPushButton* btnEliminar;
    QPushButton* btnBuscar;
    QPushButton* btnMostrar;
    QPushButton* btnVaciar;
    QPushButton* btnAnterior;
    QPushButton* btnSiguiente;

    QLineEdit* edtTitulo;
    QLineEdit* edtArtista;
    QSpinBox*  spnPosicion;

    QMediaPlayer* player;
    QAudioOutput* audioOut;

    void         limpiarTarjetas();
    QHBoxLayout* getLayoutTarjetas();
    QFrame*      crearTarjeta(const QString& titulo,
                              const QString& artista,
                              bool tieneAudio,
                              bool esActual,
                              int indice);
    QLabel*      crearFlecha();
    QLabel*      crearIndicadorCircular();
    QLabel*      crearMensajeVacio();

    void setEtiquetas(const QString& actual,
                      const QString& anterior,
                      const QString& siguiente);
    void setEstado(const QString& msg);

    QStringList pedirArchivosMusica();
    void        mostrarError(const QString& msg);
    void        mostrarInfo(const QString& msg);
    bool        confirmar(const QString& msg);

    QString getTitulo() const;
    QString getArtista() const;
    int     getPosicion() const;
    void    limpiarEntradas();

private:
    QWidget*      contenedorTarjetas;
    QHBoxLayout*  layoutTarjetas;
    QScrollArea*  scroll;
    QLabel*       lblActual;
    QLabel*       lblAnterior;
    QLabel*       lblSiguiente;
    QLabel*       lblEstado;
};

#endif
