QT += widgets multimedia
CONFIG += c++11
TARGET = LoopMusic
TEMPLATE = app

INCLUDEPATH += app model view controller utils

SOURCES += \
    app/LoopMusicApplication.cpp \
    view/VentanaPrincipal.cpp \
    controller/ReproductorController.cpp

HEADERS += \
    app/LoopMusicApplication.h \
    model/Cancion.h \
    model/Nodo.h \
    model/NodoImpl.h \
    model/ListaCircularDoble.h \
    model/ListaCircularDobleImpl.h \
    view/VentanaPrincipal.h \
    controller/ReproductorController.h \
    utils/Validaciones.h
