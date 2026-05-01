#include "Solicitud.h"
#include <iostream>

Solicitud::Solicitud()
{
    carneEstudiante = "";
    descripcion = "";
    tipo = 4;
}

Solicitud::Solicitud(const string &carne, const string &descripcion, int tipo)
{
    this->carneEstudiante = carne;
    this->descripcion = descripcion;
    this->tipo = tipo;
}

string Solicitud::getCarne() const        { return carneEstudiante; }
string Solicitud::getDescripcion() const  { return descripcion; }
int    Solicitud::getTipo() const         { return tipo; }

string Solicitud::getTipoTexto() const
{
    switch (tipo)
    {
    case 1: return "Reporte de error en material";
    case 2: return "Habilitacion de recurso";
    case 3: return "Revision de tarea";
    case 4: return "Consulta academica";
    default: return "Desconocido";
    }
}

void Solicitud::mostrar() const
{
    cout << "[" << getTipoTexto() << "] "
         << "Carne: " << carneEstudiante
         << " - " << descripcion << endl;
}
