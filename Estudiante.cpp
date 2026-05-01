#include "Estudiante.h"
#include <iostream>

Estudiante::Estudiante()
{
    carne = "";
    nombre = "";
    correo = "";
}

Estudiante::Estudiante(const string &carne, const string &nombre, const string &correo)
{
    this->carne = carne;
    this->nombre = nombre;
    this->correo = correo;
}

string Estudiante::getCarne() const  { return carne; }
string Estudiante::getNombre() const { return nombre; }
string Estudiante::getCorreo() const { return correo; }

void Estudiante::setCarne(const string &carne)   { this->carne = carne; }
void Estudiante::setNombre(const string &nombre) { this->nombre = nombre; }
void Estudiante::setCorreo(const string &correo) { this->correo = correo; }

void Estudiante::mostrar() const
{
    cout << "Carne: " << carne
         << " | Nombre: " << nombre
         << " | Correo: " << correo << endl;
}
