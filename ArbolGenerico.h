#ifndef ARBOL_GENERICO_H
#define ARBOL_GENERICO_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Arbol generico (n hijos por nodo). Inspirado en el Lab 6 (LstdTree),
// pero con metodos extra para cumplir con la consigna del proyecto:
// nivel, descendientes, altura, hojas y ruta desde la raiz.
template <class T>
class NodoGenerico
{
private:
    T valor;
    vector<NodoGenerico<T>*> hijos;

public:
    NodoGenerico() {}
    NodoGenerico(const T &valor) { this->valor = valor; }

    ~NodoGenerico()
    {
        for (size_t i = 0; i < hijos.size(); i++)
            delete hijos[i];
    }

    T& getValor()             { return valor; }
    const T& getValor() const { return valor; }

    void setValor(const T &v) { valor = v; }

    vector<NodoGenerico<T>*>& getHijos()             { return hijos; }
    const vector<NodoGenerico<T>*>& getHijos() const { return hijos; }

    NodoGenerico<T>* agregarHijo(const T &valor)
    {
        NodoGenerico<T> *nuevo = new NodoGenerico<T>(valor);
        hijos.push_back(nuevo);
        return nuevo;
    }

    bool eliminarHoja(const T &valor)
    {
        for (size_t i = 0; i < hijos.size(); i++)
        {
            if (hijos[i]->valor == valor && hijos[i]->hijos.empty())
            {
                delete hijos[i];
                hijos.erase(hijos.begin() + i);
                return true;
            }
            if (hijos[i]->eliminarHoja(valor)) return true;
        }
        return false;
    }

    NodoGenerico<T>* buscar(const T &valor)
    {
        if (this->valor == valor) return this;
        for (size_t i = 0; i < hijos.size(); i++)
        {
            NodoGenerico<T> *r = hijos[i]->buscar(valor);
            if (r != nullptr) return r;
        }
        return nullptr;
    }

    void mostrar(int profundidad = 0) const
    {
        for (int i = 0; i < profundidad; i++)
        {
            if (i != profundidad - 1) cout << "    ";
            else                      cout << "|-- ";
        }
        cout << valor << endl;
        for (size_t i = 0; i < hijos.size(); i++)
            hijos[i]->mostrar(profundidad + 1);
    }

    int nivel(const T &valor, int actual = 0) const
    {
        if (this->valor == valor) return actual;
        for (size_t i = 0; i < hijos.size(); i++)
        {
            int r = hijos[i]->nivel(valor, actual + 1);
            if (r != -1) return r;
        }
        return -1;
    }

    int contarDescendientes() const
    {
        int total = (int)hijos.size();
        for (size_t i = 0; i < hijos.size(); i++)
            total += hijos[i]->contarDescendientes();
        return total;
    }

    int altura() const
    {
        if (hijos.empty()) return 1;
        int maxH = 0;
        for (size_t i = 0; i < hijos.size(); i++)
        {
            int h = hijos[i]->altura();
            if (h > maxH) maxH = h;
        }
        return 1 + maxH;
    }

    int contarNodos() const
    {
        int total = 1;
        for (size_t i = 0; i < hijos.size(); i++)
            total += hijos[i]->contarNodos();
        return total;
    }

    void mostrarHojas() const
    {
        if (hijos.empty())
        {
            cout << "- " << valor << endl;
            return;
        }
        for (size_t i = 0; i < hijos.size(); i++)
            hijos[i]->mostrarHojas();
    }

    bool rutaHasta(const T &valor, vector<T> &ruta) const
    {
        ruta.push_back(this->valor);
        if (this->valor == valor) return true;
        for (size_t i = 0; i < hijos.size(); i++)
        {
            if (hijos[i]->rutaHasta(valor, ruta)) return true;
        }
        ruta.pop_back();
        return false;
    }
};

#endif
