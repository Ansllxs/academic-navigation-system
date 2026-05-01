#include "ListaEstudiantes.h"
#include <iostream>
#include <cctype>

// ----- helpers internos del modulo -----

static string aMinusculas(string s)
{
    for (size_t i = 0; i < s.size(); i++)
        s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

static string trim(const string &s)
{
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a])) a++;
    while (b > a && isspace((unsigned char)s[b - 1])) b--;
    return s.substr(a, b - a);
}

static bool contieneTexto(const string &grande, const string &peq)
{
    if (peq.empty()) return false;
    return aMinusculas(grande).find(aMinusculas(peq)) != string::npos;
}

// ---------------------------------------

ListaEstudiantes::ListaEstudiantes()
{
}

bool ListaEstudiantes::registrar(const Estudiante &e)
{
    // No se permiten carnes duplicados
    if (indice.contiene(e.getCarne())) return false;

    estudiantes.push_back(e);
    indice.insertar(e.getCarne(), e);
    return true;
}

bool ListaEstudiantes::modificar(const string &carne, const string &nombre, const string &correo)
{
    for (list<Estudiante>::iterator it = estudiantes.begin(); it != estudiantes.end(); ++it)
    {
        if (it->getCarne() == carne)
        {
            it->setNombre(nombre);
            it->setCorreo(correo);
            // refresca el indice (insertar reemplaza si la clave ya existe)
            indice.insertar(carne, *it);
            return true;
        }
    }
    return false;
}

bool ListaEstudiantes::eliminar(const string &carne)
{
    for (list<Estudiante>::iterator it = estudiantes.begin(); it != estudiantes.end(); ++it)
    {
        if (it->getCarne() == carne)
        {
            estudiantes.erase(it);
            indice.eliminar(carne);
            return true;
        }
    }
    return false;
}

bool ListaEstudiantes::buscarPorCarne(const string &carne, Estudiante &salida) const
{
    return indice.buscar(trim(carne), salida);
}

int ListaEstudiantes::buscarPorNombre(const string &nombre, vector<Estudiante> &salidas) const
{
    salidas.clear();
    string q = trim(nombre);
    if (q.empty()) return 0;

    for (list<Estudiante>::const_iterator it = estudiantes.begin(); it != estudiantes.end(); ++it)
    {
        if (contieneTexto(it->getNombre(), q))
            salidas.push_back(*it);
    }
    return (int)salidas.size();
}

int ListaEstudiantes::buscarPorCorreo(const string &correo, vector<Estudiante> &salidas) const
{
    salidas.clear();
    string q = trim(correo);
    if (q.empty()) return 0;

    for (list<Estudiante>::const_iterator it = estudiantes.begin(); it != estudiantes.end(); ++it)
    {
        if (contieneTexto(it->getCorreo(), q))
            salidas.push_back(*it);
    }
    return (int)salidas.size();
}

void ListaEstudiantes::mostrarTodos() const
{
    if (estudiantes.empty())
    {
        cout << "(no hay estudiantes registrados)" << endl;
        return;
    }
    for (list<Estudiante>::const_iterator it = estudiantes.begin(); it != estudiantes.end(); ++it)
    {
        it->mostrar();
    }
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
    indice.limpiar();
}
