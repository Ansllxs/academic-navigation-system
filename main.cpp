// Proyecto 1 - Sistema de administracion academica y navegacion - Angie Alpizar

#include <iostream>
#include <string>
#include <limits>

#include "Estudiante.h"
#include "ListaEstudiantes.h"
#include "ArbolGenerico.h"
#include "HistorialNavegacion.h"
#include "Solicitud.h"
#include "ColaSolicitudes.h"
#include "Persistencia.h"
#include "Reportes.h"

using namespace std;

// estado global del sistema (se pasa por referencia a los submenus)
struct Sistema
{
    ListaEstudiantes      estudiantes;
    NodoGenerico<string> *curso;
    HistorialNavegacion   historial;
    ColaSolicitudes       solicitudes;

    Sistema() { curso = nullptr; }
    ~Sistema() { if (curso != nullptr) delete curso; }
};

void menuEstudiantes(Sistema &sis)   { /* TODO */ }
void menuCursos(Sistema &sis)        { /* TODO */ }
void menuNavegacion(Sistema &sis)    { /* TODO */ }
void menuSolicitudes(Sistema &sis)   { /* TODO */ }
void menuIndice(Sistema &sis)        { /* TODO */ }
void menuReportes(Sistema &sis)      { /* TODO */ }
void guardarDatos(Sistema &sis)      { /* TODO */ }
void cargarDatos(Sistema &sis)       { /* TODO */ }

int leerOpcion()
{
    int op;
    cout << "\nOpcion: ";
    cin >> op;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return op;
}

int main()
{
    Sistema sis;
    int op = 0;

    do
    {
        cout << "\n===== Sistema academico =====" << endl;
        cout << "1. Manejo de estudiantes" << endl;
        cout << "2. Manejo de cursos y contenidos" << endl;
        cout << "3. Navegacion academica" << endl;
        cout << "4. Solicitudes pendientes" << endl;
        cout << "5. Indice de busqueda" << endl;
        cout << "6. Reportes" << endl;
        cout << "7. Guardar datos" << endl;
        cout << "8. Cargar datos" << endl;
        cout << "9. Salir" << endl;

        op = leerOpcion();

        switch (op)
        {
        case 1: menuEstudiantes(sis);  break;
        case 2: menuCursos(sis);       break;
        case 3: menuNavegacion(sis);   break;
        case 4: menuSolicitudes(sis);  break;
        case 5: menuIndice(sis);       break;
        case 6: menuReportes(sis);     break;
        case 7: guardarDatos(sis);     break;
        case 8: cargarDatos(sis);      break;
        case 9: cout << "Hasta luego." << endl; break;
        default: cout << "Opcion invalida." << endl;
        }

    } while (op != 9);

    return 0;
}
