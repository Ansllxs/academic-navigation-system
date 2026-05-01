#ifndef PILA_H
#define PILA_H

#include <iostream>
using namespace std;

template <class T>
class Pila
{
private:
    struct Nodo
    {
        T dato;
        Nodo *sig;
    };

    Nodo *tope;
    int  nElementos;

public:
    Pila();
    ~Pila();

    void push(const T &elem);
    T    pop();
    T    peek() const;

    int  num_elementos() const;
    bool Vacia() const;

    void limpiar();

    // Recorrido de tope a base aplicando una funcion lambda/funcion
    template <class F>
    void recorrer(F fn) const;
};

template <class T>
Pila<T>::Pila()
{
    tope = nullptr;
    nElementos = 0;
}

template <class T>
Pila<T>::~Pila()
{
    limpiar();
}

template <class T>
void Pila<T>::push(const T &elem)
{
    Nodo *nuevo = new Nodo;
    nuevo->dato = elem;
    nuevo->sig  = tope;
    tope = nuevo;
    nElementos++;
}

template <class T>
T Pila<T>::pop()
{
    if (tope == nullptr)
    {
        cout << " pila vacia ";
        return T();
    }
    Nodo *aux = tope;
    T valor = aux->dato;
    tope = tope->sig;
    delete aux;
    nElementos--;
    return valor;
}

template <class T>
T Pila<T>::peek() const
{
    if (tope == nullptr)
    {
        cout << " pila vacia ";
        return T();
    }
    return tope->dato;
}

template <class T>
int Pila<T>::num_elementos() const
{
    return nElementos;
}

template <class T>
bool Pila<T>::Vacia() const
{
    return tope == nullptr;
}

template <class T>
void Pila<T>::limpiar()
{
    while (tope != nullptr)
    {
        Nodo *aux = tope;
        tope = tope->sig;
        delete aux;
    }
    nElementos = 0;
}

template <class T>
template <class F>
void Pila<T>::recorrer(F fn) const
{
    Nodo *aux = tope;
    while (aux != nullptr)
    {
        fn(aux->dato);
        aux = aux->sig;
    }
}

#endif
