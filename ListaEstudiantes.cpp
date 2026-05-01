#include "ListaEstudiantes.h"
#include <iostream>

ListaEstudiantes::ListaEstudiantes()
{
}

bool ListaEstudiantes::registrar(const Estudiante &e)
{
    // TODO: validar que el carne no exista ya en el ABB
    return false;
}

bool ListaEstudiantes::modificar(const string &carne, const string &nombre, const string &correo)
{
    // TODO: buscar en la lista, modificar, refrescar el indice
    return false;
}

bool ListaEstudiantes::eliminar(const string &carne)
{
    // TODO: borrar de la lista y del ABB
    return false;
}

bool ListaEstudiantes::buscarPorCarne(const string &carne, Estudiante &salida) const
{
    return indice.buscar(carne, salida);
}

bool ListaEstudiantes::buscarPorNombre(const string &nombre, Estudiante &salida) const
{
    // TODO: recorrer la lista comparando nombre
    return false;
}

bool ListaEstudiantes::buscarPorCorreo(const string &correo, Estudiante &salida) const
{
    // TODO: recorrer la lista comparando correo
    return false;
}

void ListaEstudiantes::mostrarTodos() const
{
    // TODO: imprimir cada estudiante de la lista
}

int ListaEstudiantes::cantidad() const
{
    return (int)estudiantes.size();
}

const list<Estudiante>& ListaEstudiantes::getEstudiantes() const
{
    return estudiantes;
}

const ABB<string, Estudiante>& ListaEstudiantes::getIndice() const
{
    return indice;
}

void ListaEstudiantes::limpiar()
{
    estudiantes.clear();
    // el ABB se vacia al destruirse o al reasignarse
}
