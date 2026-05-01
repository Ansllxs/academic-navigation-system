#include "Reportes.h"
#include <iostream>

void Reportes::listaCompletaEstudiantes(const ListaEstudiantes &lista)
{
    cout << "=== Lista de estudiantes ===" << endl;
    lista.mostrarTodos();
}

void Reportes::abbInorden(const ListaEstudiantes &lista)
{
    cout << "=== ABB en inorden (carnes) ===" << endl;
    lista.getIndice().inorden();
    cout << endl;
}

void Reportes::estructuraCurso(const NodoGenerico<string> *raiz)
{
    cout << "=== Estructura del curso ===" << endl;
    if (raiz == nullptr) { cout << "(no hay curso cargado)" << endl; return; }
    raiz->mostrar();
}

void Reportes::historialEstudiante(const HistorialNavegacion &hist, const string &carne)
{
    cout << "=== Historial del estudiante " << carne << " ===" << endl;
    hist.mostrarHistorial();
}

void Reportes::solicitudesPendientes(const ColaSolicitudes &cola)
{
    cout << "=== Solicitudes pendientes ===" << endl;
    cola.mostrarTodas();
}

void Reportes::cantidadNodosArbol(const NodoGenerico<string> *raiz)
{
    if (raiz == nullptr) { cout << "Nodos del arbol: 0" << endl; return; }
    cout << "Nodos del arbol: " << raiz->contarNodos() << endl;
}

void Reportes::alturaArbol(const NodoGenerico<string> *raiz)
{
    if (raiz == nullptr) { cout << "Altura del arbol: 0" << endl; return; }
    cout << "Altura del arbol: " << raiz->altura() << endl;
}

void Reportes::cantidadEstudiantes(const ListaEstudiantes &lista)
{
    cout << "Cantidad de estudiantes: " << lista.cantidad() << endl;
}

void Reportes::menorYMayorCarne(const ListaEstudiantes &lista)
{
    string carneMin, carneMax;
    Estudiante e;

    if (lista.getIndice().minimo(carneMin, e))
        cout << "Menor carne: " << carneMin << endl;
    else
        cout << "(no hay estudiantes)" << endl;

    if (lista.getIndice().maximo(carneMax, e))
        cout << "Mayor carne: " << carneMax << endl;
}

void Reportes::recursosHoja(const NodoGenerico<string> *raiz)
{
    cout << "=== Recursos hoja del curso ===" << endl;
    if (raiz == nullptr) { cout << "(no hay curso cargado)" << endl; return; }
    raiz->mostrarHojas();
}
