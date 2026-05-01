#ifndef COLA_H
#define COLA_H

#include <iostream>
using namespace std;

template <class T>
class Cola
{
private:
    struct Nodo
    {
        T dato;
        Nodo *sig;
    };

    Nodo *frente;
    Nodo *fin;
    int  nElementos;

public:
    Cola();
    ~Cola();

    void push(const T &elem);
    T    pop();
    T    peek() const;

    int  num_elementos() const;
    bool Vacia() const;

    void limpiar();

    template <class F>
    void recorrer(F fn) const;
};

template <class T>
Cola<T>::Cola()
{
    frente = nullptr;
    fin    = nullptr;
    nElementos = 0;
}

template <class T>
Cola<T>::~Cola()
{
    limpiar();
}

template <class T>
void Cola<T>::push(const T &elem)
{
    Nodo *nuevo = new Nodo;
    nuevo->dato = elem;
    nuevo->sig  = nullptr;

    if (frente == nullptr)
        frente = nuevo;
    else
        fin->sig = nuevo;

    fin = nuevo;
    nElementos++;
}

template <class T>
T Cola<T>::pop()
{
    if (frente == nullptr)
    {
        cout << " cola vacia ";
        return T();
    }
    Nodo *aux = frente;
    T valor = aux->dato;
    frente = frente->sig;
    if (frente == nullptr) fin = nullptr;
    delete aux;
    nElementos--;
    return valor;
}

template <class T>
T Cola<T>::peek() const
{
    if (frente == nullptr)
    {
        cout << " cola vacia ";
        return T();
    }
    return frente->dato;
}

template <class T>
int Cola<T>::num_elementos() const
{
    return nElementos;
}

template <class T>
bool Cola<T>::Vacia() const
{
    return frente == nullptr;
}

template <class T>
void Cola<T>::limpiar()
{
    while (frente != nullptr)
    {
        Nodo *aux = frente;
        frente = frente->sig;
        delete aux;
    }
    fin = nullptr;
    nElementos = 0;
}

template <class T>
template <class F>
void Cola<T>::recorrer(F fn) const
{
    Nodo *aux = frente;
    while (aux != nullptr)
    {
        fn(aux->dato);
        aux = aux->sig;
    }
}

#endif
