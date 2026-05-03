#include "Reportes.h"
#include <iostream>
#include <fstream>
#include <ctime>

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

bool Reportes::exportarTodos(const string &ruta,
                             const ListaEstudiantes &lista,
                             const NodoGenerico<string> *curso,
                             const ColaSolicitudes &cola,
                             const map<string, HistorialNavegacion> &historiales)
{
    ofstream archivo(ruta.c_str());
    if (!archivo.is_open()) return false;

    // Truco: redirigir el buffer de cout al archivo para reusar las
    // funciones de reporte sin tener que refactorizarlas.
    streambuf *bufOriginal = cout.rdbuf();
    cout.rdbuf(archivo.rdbuf());

    time_t ahora = time(nullptr);
    char fechaBuf[64];
    strftime(fechaBuf, sizeof(fechaBuf), "%Y-%m-%d %H:%M:%S", localtime(&ahora));

    cout << "============================================" << endl;
    cout << "  REPORTES DEL SISTEMA ACADEMICO" << endl;
    cout << "  Generado: " << fechaBuf << endl;
    cout << "============================================" << endl << endl;

    cout << "--- Reporte 1: Lista completa de estudiantes ---" << endl;
    listaCompletaEstudiantes(lista);
    cout << endl;

    cout << "--- Reporte 2: Recorrido del ABB en inorden ---" << endl;
    abbInorden(lista);
    cout << endl;

    cout << "--- Reporte 3: Estructura jerarquica del curso ---" << endl;
    estructuraCurso(curso);
    cout << endl;

    cout << "--- Reporte 4: Historial de navegacion por estudiante ---" << endl;
    if (historiales.empty())
    {
        cout << "(no hay historiales registrados)" << endl;
    }
    else
    {
        map<string, HistorialNavegacion>::const_iterator it;
        for (it = historiales.begin(); it != historiales.end(); ++it)
        {
            historialEstudiante(it->second, it->first);
            cout << endl;
        }
    }

    cout << "--- Reporte 5: Solicitudes pendientes en cola ---" << endl;
    solicitudesPendientes(cola);
    cout << endl;

    cout << "--- Reporte 6: Cantidad de nodos del arbol generico ---" << endl;
    cantidadNodosArbol(curso);
    cout << endl;

    cout << "--- Reporte 7: Altura del arbol generico ---" << endl;
    alturaArbol(curso);
    cout << endl;

    cout << "--- Reporte 8: Cantidad de estudiantes registrados ---" << endl;
    cantidadEstudiantes(lista);
    cout << endl;

    cout << "--- Reporte 9: Estudiante con menor y mayor carne ---" << endl;
    menorYMayorCarne(lista);
    cout << endl;

    cout << "--- Reporte 10: Recursos hoja del arbol del curso ---" << endl;
    recursosHoja(curso);
    cout << endl;

    cout.rdbuf(bufOriginal);
    archivo.close();
    return true;
}
