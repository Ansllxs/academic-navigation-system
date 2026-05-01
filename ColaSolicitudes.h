#ifndef COLA_SOLICITUDES_H
#define COLA_SOLICITUDES_H

#include "Cola.h"
#include "Solicitud.h"

// Administra las solicitudes con dos colas:
// - urgentes: para tipo 1 y 2 (errores y habilitaciones)
// - normales: para tipo 3 y 4 (revisiones y consultas)
// Al atender, primero se vacian las urgentes y despues las normales.
class ColaSolicitudes
{
private:
    Cola<Solicitud> urgentes;
    Cola<Solicitud> normales;

public:
    ColaSolicitudes();

    void insertar(const Solicitud &s);
    bool atender(Solicitud &salida);
    bool frente(Solicitud &salida) const;

    void mostrarTodas() const;
    int  cantidadPendientes() const;

    bool Vacia() const;

    const Cola<Solicitud>& getUrgentes() const;
    const Cola<Solicitud>& getNormales() const;

    void limpiar();
};

#endif
