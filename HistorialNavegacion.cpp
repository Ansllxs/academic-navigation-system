#include "HistorialNavegacion.h"
#include <iostream>

HistorialNavegacion::HistorialNavegacion()
{
}

void HistorialNavegacion::registrarVisita(const string &nodo)
{
    historial.push(nodo);
}

void HistorialNavegacion::registrarAccion(const string &accion)
{
    acciones.push(accion);
}

string HistorialNavegacion::retroceder()
{
    if (historial.Vacia()) return "";
    return historial.pop();
}

string HistorialNavegacion::deshacerAccion()
{
    if (acciones.Vacia()) return "";
    return acciones.pop();
}

void HistorialNavegacion::mostrarHistorial() const
{
    if (historial.Vacia())
    {
        cout << "(historial vacio)" << endl;
        return;
    }
    int i = 1;
    historial.recorrer([&](const string &s)
    {
        cout << i++ << ". " << s << endl;
    });
}

void HistorialNavegacion::mostrarAcciones() const
{
    if (acciones.Vacia())
    {
        cout << "(no hay acciones registradas)" << endl;
        return;
    }
    int i = 1;
    acciones.recorrer([&](const string &s)
    {
        cout << i++ << ". " << s << endl;
    });
}

void HistorialNavegacion::limpiarHistorial() { historial.limpiar(); }
void HistorialNavegacion::limpiarAcciones()  { acciones.limpiar(); }

bool HistorialNavegacion::hayHistorial() const { return !historial.Vacia(); }
bool HistorialNavegacion::hayAcciones()  const { return !acciones.Vacia(); }
