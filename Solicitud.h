#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <string>
using namespace std;

// Tipos posibles de solicitud. Las primeras tienen mayor prioridad.
// 1 = error material (mas urgente)
// 2 = habilitacion de recurso
// 3 = revision de tarea
// 4 = consulta academica
class Solicitud
{
private:
    string carneEstudiante;
    string descripcion;
    int tipo;

public:
    Solicitud();
    Solicitud(const string &carne, const string &descripcion, int tipo);

    string getCarne() const;
    string getDescripcion() const;
    int getTipo() const;
    string getTipoTexto() const;

    void mostrar() const;
};

#endif
