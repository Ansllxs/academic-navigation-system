#ifndef LISTA_ESTUDIANTES_H
#define LISTA_ESTUDIANTES_H

#include <list>
#include <vector>
#include <string>
#include "Estudiante.h"
#include "ABB.h"
using namespace std;

// Maneja la lista de estudiantes y su indice por carne en un ABB.
// Las dos estructuras siempre se mantienen sincronizadas.
class ListaEstudiantes
{
private:
    list<Estudiante> estudiantes;
    ABB<string, Estudiante> indice;

public:
    ListaEstudiantes();

    bool registrar(const Estudiante &e);
    bool modificar(const string &carne, const string &nombre, const string &correo);
    bool eliminar(const string &carne);

    bool buscarPorCarne(const string &carne, Estudiante &salida) const;
    int  buscarPorNombre(const string &nombre, vector<Estudiante> &salidas) const;
    int  buscarPorCorreo(const string &correo, vector<Estudiante> &salidas) const;

    void mostrarTodos() const;
    int  cantidad() const;

    // accesos para reportes y persistencia
    const list<Estudiante>& getEstudiantes() const;
    const ABB<string, Estudiante>& getIndice() const;

    void limpiar();
};

#endif
