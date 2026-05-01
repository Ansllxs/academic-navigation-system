#ifndef ABB_H
#define ABB_H

#include <iostream>
using namespace std;

// Arbol binario de busqueda generico.
// K = tipo de la clave (debe soportar < y ==)
// V = tipo del valor asociado a la clave
template <class K, class V>
class ABB
{
private:
    struct Nodo
    {
        K clave;
        V valor;
        Nodo *izq;
        Nodo *der;
    };

    Nodo *raiz;
    int  nNodos;

    // metodos privados recursivos
    Nodo* insertarRec(Nodo *n, const K &clave, const V &valor);
    Nodo* buscarRec(Nodo *n, const K &clave) const;
    Nodo* eliminarRec(Nodo *n, const K &clave);
    Nodo* minimoRec(Nodo *n) const;
    Nodo* maximoRec(Nodo *n) const;
    int   alturaRec(Nodo *n) const;
    void  inordenRec(Nodo *n) const;
    void  preordenRec(Nodo *n) const;
    void  postordenRec(Nodo *n) const;
    void  destruir(Nodo *n);

public:
    ABB();
    ~ABB();

    void insertar(const K &clave, const V &valor);
    bool buscar(const K &clave, V &valorSalida) const;
    bool contiene(const K &clave) const;
    void eliminar(const K &clave);

    void inorden() const;
    void preorden() const;
    void postorden() const;

    bool minimo(K &claveSalida, V &valorSalida) const;
    bool maximo(K &claveSalida, V &valorSalida) const;

    int  altura() const;
    int  contar() const;
    bool Vacia() const;

    void limpiar();
};

template <class K, class V>
ABB<K,V>::ABB()
{
    raiz = nullptr;
    nNodos = 0;
}

template <class K, class V>
ABB<K,V>::~ABB()
{
    destruir(raiz);
}

template <class K, class V>
void ABB<K,V>::destruir(Nodo *n)
{
    if (n == nullptr) return;
    destruir(n->izq);
    destruir(n->der);
    delete n;
}

template <class K, class V>
typename ABB<K,V>::Nodo* ABB<K,V>::insertarRec(Nodo *n, const K &clave, const V &valor)
{
    if (n == nullptr)
    {
        Nodo *nuevo = new Nodo;
        nuevo->clave = clave;
        nuevo->valor = valor;
        nuevo->izq = nullptr;
        nuevo->der = nullptr;
        nNodos++;
        return nuevo;
    }
    if (clave < n->clave)      n->izq = insertarRec(n->izq, clave, valor);
    else if (n->clave < clave) n->der = insertarRec(n->der, clave, valor);
    else                       n->valor = valor;
    return n;
}

template <class K, class V>
void ABB<K,V>::insertar(const K &clave, const V &valor)
{
    raiz = insertarRec(raiz, clave, valor);
}

template <class K, class V>
typename ABB<K,V>::Nodo* ABB<K,V>::buscarRec(Nodo *n, const K &clave) const
{
    if (n == nullptr) return nullptr;
    if (clave < n->clave)      return buscarRec(n->izq, clave);
    else if (n->clave < clave) return buscarRec(n->der, clave);
    else                       return n;
}

template <class K, class V>
bool ABB<K,V>::buscar(const K &clave, V &valorSalida) const
{
    Nodo *n = buscarRec(raiz, clave);
    if (n == nullptr) return false;
    valorSalida = n->valor;
    return true;
}

template <class K, class V>
bool ABB<K,V>::contiene(const K &clave) const
{
    return buscarRec(raiz, clave) != nullptr;
}

template <class K, class V>
typename ABB<K,V>::Nodo* ABB<K,V>::minimoRec(Nodo *n) const
{
    if (n == nullptr) return nullptr;
    while (n->izq != nullptr) n = n->izq;
    return n;
}

template <class K, class V>
typename ABB<K,V>::Nodo* ABB<K,V>::maximoRec(Nodo *n) const
{
    if (n == nullptr) return nullptr;
    while (n->der != nullptr) n = n->der;
    return n;
}

template <class K, class V>
typename ABB<K,V>::Nodo* ABB<K,V>::eliminarRec(Nodo *n, const K &clave)
{
    if (n == nullptr) return nullptr;

    if (clave < n->clave)
    {
        n->izq = eliminarRec(n->izq, clave);
    }
    else if (n->clave < clave)
    {
        n->der = eliminarRec(n->der, clave);
    }
    else
    {
        // hoja
        if (n->izq == nullptr && n->der == nullptr)
        {
            delete n;
            nNodos--;
            return nullptr;
        }
        // un solo hijo
        if (n->izq == nullptr)
        {
            Nodo *aux = n->der;
            delete n;
            nNodos--;
            return aux;
        }
        if (n->der == nullptr)
        {
            Nodo *aux = n->izq;
            delete n;
            nNodos--;
            return aux;
        }
        // dos hijos: tomar minimo del subarbol derecho
        Nodo *suc = minimoRec(n->der);
        n->clave = suc->clave;
        n->valor = suc->valor;
        n->der = eliminarRec(n->der, suc->clave);
    }
    return n;
}

template <class K, class V>
void ABB<K,V>::eliminar(const K &clave)
{
    raiz = eliminarRec(raiz, clave);
}

template <class K, class V>
void ABB<K,V>::inordenRec(Nodo *n) const
{
    if (n == nullptr) return;
    inordenRec(n->izq);
    cout << n->clave << " ";
    inordenRec(n->der);
}

template <class K, class V>
void ABB<K,V>::preordenRec(Nodo *n) const
{
    if (n == nullptr) return;
    cout << n->clave << " ";
    preordenRec(n->izq);
    preordenRec(n->der);
}

template <class K, class V>
void ABB<K,V>::postordenRec(Nodo *n) const
{
    if (n == nullptr) return;
    postordenRec(n->izq);
    postordenRec(n->der);
    cout << n->clave << " ";
}

template <class K, class V>
void ABB<K,V>::inorden()   const { inordenRec(raiz); }

template <class K, class V>
void ABB<K,V>::preorden()  const { preordenRec(raiz); }

template <class K, class V>
void ABB<K,V>::postorden() const { postordenRec(raiz); }

template <class K, class V>
bool ABB<K,V>::minimo(K &claveSalida, V &valorSalida) const
{
    Nodo *n = minimoRec(raiz);
    if (n == nullptr) return false;
    claveSalida = n->clave;
    valorSalida = n->valor;
    return true;
}

template <class K, class V>
bool ABB<K,V>::maximo(K &claveSalida, V &valorSalida) const
{
    Nodo *n = maximoRec(raiz);
    if (n == nullptr) return false;
    claveSalida = n->clave;
    valorSalida = n->valor;
    return true;
}

template <class K, class V>
int ABB<K,V>::alturaRec(Nodo *n) const
{
    if (n == nullptr) return 0;
    int hi = alturaRec(n->izq);
    int hd = alturaRec(n->der);
    return 1 + (hi > hd ? hi : hd);
}

template <class K, class V>
int ABB<K,V>::altura() const
{
    return alturaRec(raiz);
}

template <class K, class V>
int ABB<K,V>::contar() const
{
    return nNodos;
}

template <class K, class V>
bool ABB<K,V>::Vacia() const
{
    return raiz == nullptr;
}

template <class K, class V>
void ABB<K,V>::limpiar()
{
    destruir(raiz);
    raiz = nullptr;
    nNodos = 0;
}

#endif
