#ifndef HISTORIAL_NAVEGACION_H
#define HISTORIAL_NAVEGACION_H

#include <string>
#include "Pila.h"
using namespace std;

// Mantiene el historial de navegacion del estudiante con una pila,
// y una pila aparte para deshacer la ultima accion academica.
class HistorialNavegacion
{
private:
    Pila<string> historial;
    Pila<string> acciones;

public:
    HistorialNavegacion();

    void registrarVisita(const string &nodo);
    void registrarAccion(const string &accion);

    string retroceder();      // saca el ultimo de historial
    string deshacerAccion();  // saca la ultima accion

    void mostrarHistorial() const;
    void mostrarAcciones() const;

    void limpiarHistorial();
    void limpiarAcciones();

    bool hayHistorial() const;
    bool hayAcciones()  const;
};

#endif
