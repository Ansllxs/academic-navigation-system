// Proyecto 1 - Sistema de administracion academica y navegacion - Angie Alpizar

#include <iostream>
#include <string>
#include <vector>
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

string leerLinea(const string &prompt)
{
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

void menuEstudiantes(Sistema &sis)
{
    int op;
    do
    {
        cout << "\n--- Manejo de estudiantes ---" << endl;
        cout << "1. Registrar estudiante" << endl;
        cout << "2. Modificar estudiante" << endl;
        cout << "3. Eliminar estudiante" << endl;
        cout << "4. Mostrar todos" << endl;
        cout << "5. Buscar por carne" << endl;
        cout << "6. Buscar por nombre" << endl;
        cout << "7. Buscar por correo" << endl;
        cout << "0. Volver" << endl;

        op = leerOpcion();

        string carne, nombre, correo;
        Estudiante e;

        switch (op)
        {
        case 1:
            carne  = leerLinea("Carne: ");
            nombre = leerLinea("Nombre: ");
            correo = leerLinea("Correo: ");
            if (carne.empty() || nombre.empty() || correo.empty())
                cout << "Datos invalidos. Ningun campo puede estar vacio." << endl;
            else if (sis.estudiantes.registrar(Estudiante(carne, nombre, correo)))
                cout << "Estudiante registrado correctamente." << endl;
            else
                cout << "Ya existe un estudiante con ese carne." << endl;
            break;

        case 2:
            carne = leerLinea("Carne del estudiante a modificar: ");
            if (!sis.estudiantes.buscarPorCarne(carne, e))
            {
                cout << "Estudiante no encontrado." << endl;
                break;
            }
            nombre = leerLinea("Nuevo nombre: ");
            correo = leerLinea("Nuevo correo: ");
            if (nombre.empty() || correo.empty())
                cout << "Datos invalidos." << endl;
            else if (sis.estudiantes.modificar(carne, nombre, correo))
                cout << "Estudiante modificado." << endl;
            else
                cout << "No se pudo modificar." << endl;
            break;

        case 3:
            carne = leerLinea("Carne del estudiante a eliminar: ");
            if (sis.estudiantes.eliminar(carne))
                cout << "Estudiante eliminado." << endl;
            else
                cout << "Estudiante no encontrado." << endl;
            break;

        case 4:
            cout << "\n--- Lista de estudiantes ---" << endl;
            sis.estudiantes.mostrarTodos();
            break;

        case 5:
            carne = leerLinea("Carne a buscar: ");
            if (sis.estudiantes.buscarPorCarne(carne, e))
            {
                cout << "Encontrado: ";
                e.mostrar();
            }
            else
                cout << "Estudiante no encontrado." << endl;
            break;

        case 6:
        {
            nombre = leerLinea("Nombre (o parte del nombre): ");
            vector<Estudiante> resultados;
            int n = sis.estudiantes.buscarPorNombre(nombre, resultados);
            if (n == 0)
                cout << "No se encontro ningun estudiante." << endl;
            else
            {
                cout << "Se encontraron " << n << " coincidencia(s):" << endl;
                for (size_t i = 0; i < resultados.size(); i++)
                    resultados[i].mostrar();
            }
            break;
        }

        case 7:
        {
            correo = leerLinea("Correo (o parte del correo): ");
            vector<Estudiante> resultados;
            int n = sis.estudiantes.buscarPorCorreo(correo, resultados);
            if (n == 0)
                cout << "No se encontro ningun estudiante." << endl;
            else
            {
                cout << "Se encontraron " << n << " coincidencia(s):" << endl;
                for (size_t i = 0; i < resultados.size(); i++)
                    resultados[i].mostrar();
            }
            break;
        }

        case 0:
            break;

        default:
            cout << "Opcion invalida." << endl;
        }

    } while (op != 0);
}

void menuCursos(Sistema &)        { cout << "(pendiente)" << endl; }
void menuNavegacion(Sistema &)    { cout << "(pendiente)" << endl; }
void menuSolicitudes(Sistema &)   { cout << "(pendiente)" << endl; }
void menuIndice(Sistema &)        { cout << "(pendiente)" << endl; }
void menuReportes(Sistema &)      { cout << "(pendiente)" << endl; }
void guardarDatos(Sistema &)      { cout << "(pendiente)" << endl; }
void cargarDatos(Sistema &)       { cout << "(pendiente)" << endl; }

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
