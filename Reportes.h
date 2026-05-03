#ifndef REPORTES_H
#define REPORTES_H

#include <string>
#include <map>
#include "ListaEstudiantes.h"
#include "ArbolGenerico.h"
#include "HistorialNavegacion.h"
#include "ColaSolicitudes.h"
using namespace std;

// Los 10 reportes obligatorios de la consigna.
namespace Reportes
{
    void listaCompletaEstudiantes(const ListaEstudiantes &lista);
    void abbInorden(const ListaEstudiantes &lista);
    void estructuraCurso(const NodoGenerico<string> *raiz);
    void historialEstudiante(const HistorialNavegacion &hist, const string &carne);
    void solicitudesPendientes(const ColaSolicitudes &cola);
    void cantidadNodosArbol(const NodoGenerico<string> *raiz);
    void alturaArbol(const NodoGenerico<string> *raiz);
    void cantidadEstudiantes(const ListaEstudiantes &lista);
    void menorYMayorCarne(const ListaEstudiantes &lista);
    void recursosHoja(const NodoGenerico<string> *raiz);

    // Exporta los 10 reportes a un archivo de texto.
    // Devuelve true si pudo escribir el archivo.
    bool exportarTodos(const string &ruta,
                       const ListaEstudiantes &lista,
                       const NodoGenerico<string> *curso,
                       const ColaSolicitudes &cola,
                       const map<string, HistorialNavegacion> &historiales);
}

#endif
