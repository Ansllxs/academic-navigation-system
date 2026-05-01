#include "Persistencia.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Persistencia::guardarEstudiantes(const ListaEstudiantes &lista, const string &ruta)
{
    // TODO: escribir cada estudiante en una linea: carne;nombre;correo
    return false;
}

bool Persistencia::cargarEstudiantes(ListaEstudiantes &lista, const string &ruta)
{
    // TODO: leer linea a linea y registrar cada estudiante
    return false;
}

bool Persistencia::guardarCurso(const NodoGenerico<string> *raiz, const string &ruta)
{
    // TODO: serializar el arbol generico (ej. "padre>hijo" por linea
    // o algun formato indentado)
    return false;
}

NodoGenerico<string>* Persistencia::cargarCurso(const string &ruta)
{
    // TODO: reconstruir el arbol desde el archivo
    return nullptr;
}

bool Persistencia::guardarSolicitudes(const ColaSolicitudes &cola, const string &ruta)
{
    // TODO: escribir tipo;carne;descripcion por linea
    return false;
}

bool Persistencia::cargarSolicitudes(ColaSolicitudes &cola, const string &ruta)
{
    // TODO: leer linea a linea y reinsertar
    return false;
}
