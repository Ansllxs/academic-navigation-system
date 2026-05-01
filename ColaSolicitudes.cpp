#include "ColaSolicitudes.h"
#include <iostream>

ColaSolicitudes::ColaSolicitudes()
{
}

void ColaSolicitudes::insertar(const Solicitud &s)
{
    if (s.getTipo() == 1 || s.getTipo() == 2)
        urgentes.push(s);
    else
        normales.push(s);
}

bool ColaSolicitudes::atender(Solicitud &salida)
{
    if (!urgentes.Vacia())
    {
        salida = urgentes.pop();
        return true;
    }
    if (!normales.Vacia())
    {
        salida = normales.pop();
        return true;
    }
    return false;
}

bool ColaSolicitudes::frente(Solicitud &salida) const
{
    if (!urgentes.Vacia()) { salida = urgentes.peek(); return true; }
    if (!normales.Vacia()) { salida = normales.peek(); return true; }
    return false;
}

void ColaSolicitudes::mostrarTodas() const
{
    if (Vacia())
    {
        cout << "(no hay solicitudes pendientes)" << endl;
        return;
    }

    cout << "--- Urgentes ---" << endl;
    if (urgentes.Vacia()) cout << "(ninguna)" << endl;
    else urgentes.recorrer([](const Solicitud &s){ s.mostrar(); });

    cout << "--- Normales ---" << endl;
    if (normales.Vacia()) cout << "(ninguna)" << endl;
    else normales.recorrer([](const Solicitud &s){ s.mostrar(); });
}

int ColaSolicitudes::cantidadPendientes() const
{
    return urgentes.num_elementos() + normales.num_elementos();
}

bool ColaSolicitudes::Vacia() const
{
    return urgentes.Vacia() && normales.Vacia();
}

const Cola<Solicitud>& ColaSolicitudes::getUrgentes() const { return urgentes; }
const Cola<Solicitud>& ColaSolicitudes::getNormales() const { return normales; }

void ColaSolicitudes::limpiar()
{
    urgentes.limpiar();
    normales.limpiar();
}
