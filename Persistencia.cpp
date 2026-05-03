#include "Persistencia.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

// ====================== ESTUDIANTES ======================

bool Persistencia::guardarEstudiantes(const ListaEstudiantes &lista, const string &ruta)
{
    ofstream f(ruta);
    if (!f.is_open()) return false;

    const list<Estudiante> &estudiantes = lista.getEstudiantes();
    for (list<Estudiante>::const_iterator it = estudiantes.begin(); it != estudiantes.end(); ++it)
    {
        f << it->getCarne()  << "|"
          << it->getNombre() << "|"
          << it->getCorreo() << "\n";
    }
    f.close();
    return true;
}

bool Persistencia::cargarEstudiantes(ListaEstudiantes &lista, const string &ruta)
{
    ifstream f(ruta);
    if (!f.is_open()) return false;

    lista.limpiar();

    string linea;
    while (getline(f, linea))
    {
        if (linea.empty()) continue;

        size_t p1 = linea.find('|');
        if (p1 == string::npos) continue;
        size_t p2 = linea.find('|', p1 + 1);
        if (p2 == string::npos) continue;

        string carne  = linea.substr(0, p1);
        string nombre = linea.substr(p1 + 1, p2 - p1 - 1);
        string correo = linea.substr(p2 + 1);

        lista.registrar(Estudiante(carne, nombre, correo));
    }
    f.close();
    return true;
}

// ====================== CURSO (arbol generico) ======================

// helper recursivo: imprime el nodo y todos sus descendientes en preorden
static void escribirNodo(ofstream &f, const NodoGenerico<string> *n, int profundidad)
{
    f << profundidad << "|" << n->getValor() << "\n";
    const vector<NodoGenerico<string>*> &hijos = n->getHijos();
    for (size_t i = 0; i < hijos.size(); i++)
        escribirNodo(f, hijos[i], profundidad + 1);
}

bool Persistencia::guardarCurso(const NodoGenerico<string> *raiz, const string &ruta)
{
    ofstream f(ruta);
    if (!f.is_open()) return false;

    if (raiz != nullptr) escribirNodo(f, raiz, 0);

    f.close();
    return true;
}

NodoGenerico<string>* Persistencia::cargarCurso(const string &ruta)
{
    ifstream f(ruta);
    if (!f.is_open()) return nullptr;

    NodoGenerico<string> *raiz = nullptr;
    // ultimo[d] = ultimo nodo creado a profundidad d
    vector<NodoGenerico<string>*> ultimo;

    string linea;
    while (getline(f, linea))
    {
        if (linea.empty()) continue;
        size_t p = linea.find('|');
        if (p == string::npos) continue;

        int profundidad;
        try { profundidad = stoi(linea.substr(0, p)); }
        catch (...) { if (raiz) delete raiz; return nullptr; }

        string valor = linea.substr(p + 1);

        if (profundidad == 0)
        {
            if (raiz != nullptr) { delete raiz; return nullptr; } // archivo invalido: dos raices
            raiz = new NodoGenerico<string>(valor);
            ultimo.assign(1, raiz);
        }
        else
        {
            if (profundidad - 1 >= (int)ultimo.size() || ultimo[profundidad - 1] == nullptr)
            {
                if (raiz) delete raiz;
                return nullptr;
            }
            NodoGenerico<string> *padre = ultimo[profundidad - 1];
            NodoGenerico<string> *hijo  = padre->agregarHijo(valor);

            if (profundidad >= (int)ultimo.size()) ultimo.resize(profundidad + 1, nullptr);
            ultimo[profundidad] = hijo;
        }
    }
    f.close();
    return raiz;
}

// ====================== SOLICITUDES ======================

bool Persistencia::guardarSolicitudes(const ColaSolicitudes &cola, const string &ruta)
{
    ofstream f(ruta);
    if (!f.is_open()) return false;

    // Las recorremos: urgentes primero, despues normales.
    // Al cargar, insertar() las pone en la cola correcta segun el tipo.
    cola.getUrgentes().recorrer([&](const Solicitud &s)
    {
        f << s.getTipo() << "|" << s.getCarne() << "|" << s.getDescripcion() << "\n";
    });
    cola.getNormales().recorrer([&](const Solicitud &s)
    {
        f << s.getTipo() << "|" << s.getCarne() << "|" << s.getDescripcion() << "\n";
    });

    f.close();
    return true;
}

bool Persistencia::cargarSolicitudes(ColaSolicitudes &cola, const string &ruta)
{
    ifstream f(ruta);
    if (!f.is_open()) return false;

    cola.limpiar();

    string linea;
    while (getline(f, linea))
    {
        if (linea.empty()) continue;

        size_t p1 = linea.find('|');
        if (p1 == string::npos) continue;
        size_t p2 = linea.find('|', p1 + 1);
        if (p2 == string::npos) continue;

        int tipo;
        try { tipo = stoi(linea.substr(0, p1)); }
        catch (...) { continue; }

        string carne = linea.substr(p1 + 1, p2 - p1 - 1);
        string desc  = linea.substr(p2 + 1);

        cola.insertar(Solicitud(carne, desc, tipo));
    }
    f.close();
    return true;
}
