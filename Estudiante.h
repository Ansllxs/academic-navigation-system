#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
using namespace std;

class Estudiante
{
private:
    string carne;
    string nombre;
    string correo;

public:
    Estudiante();
    Estudiante(const string &carne, const string &nombre, const string &correo);

    string getCarne() const;
    string getNombre() const;
    string getCorreo() const;

    void setCarne(const string &carne);
    void setNombre(const string &nombre);
    void setCorreo(const string &correo);

    void mostrar() const;
};

#endif
