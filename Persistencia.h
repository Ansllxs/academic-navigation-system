#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <string>
#include "ListaEstudiantes.h"
#include "ArbolGenerico.h"
#include "ColaSolicitudes.h"
using namespace std;

// Funciones para guardar y cargar el estado en archivos de texto
// dentro de la carpeta data/.
namespace Persistencia
{
    bool guardarEstudiantes(const ListaEstudiantes &lista, const string &ruta);
    bool cargarEstudiantes(ListaEstudiantes &lista, const string &ruta);

    bool guardarCurso(const NodoGenerico<string> *raiz, const string &ruta);
    NodoGenerico<string>* cargarCurso(const string &ruta);

    bool guardarSolicitudes(const ColaSolicitudes &cola, const string &ruta);
    bool cargarSolicitudes(ColaSolicitudes &cola, const string &ruta);
}

#endif
