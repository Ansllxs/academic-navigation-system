// Proyecto 1 - Sistema de administracion academica y navegacion - Angie Alpizar

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cctype>

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
    ListaEstudiantes                       estudiantes;
    NodoGenerico<string>                  *curso;
    map<string, HistorialNavegacion>       historiales;  // un historial por carne
    ColaSolicitudes                        solicitudes;

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

    // limpia espacios y tabs al inicio y al final para evitar errores
    // tipo "Conjuntos " vs "Conjuntos"
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a])) a++;
    while (b > a && isspace((unsigned char)s[b - 1])) b--;
    return s.substr(a, b - a);
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

void menuCursos(Sistema &sis)
{
    int op;
    do
    {
        cout << "\n--- Manejo de cursos y contenidos ---" << endl;
        cout << "1.  Crear curso (raiz)" << endl;
        cout << "2.  Agregar nodo hijo" << endl;
        cout << "3.  Eliminar nodo hoja" << endl;
        cout << "4.  Mostrar arbol completo" << endl;
        cout << "5.  Buscar nodo por nombre" << endl;
        cout << "6.  Mostrar nivel de un nodo" << endl;
        cout << "7.  Contar descendientes de un nodo" << endl;
        cout << "8.  Altura del arbol" << endl;
        cout << "9.  Mostrar nodos hoja (recursos)" << endl;
        cout << "10. Mostrar ruta desde la raiz a un nodo" << endl;
        cout << "0.  Volver" << endl;

        op = leerOpcion();

        switch (op)
        {
        case 1:
        {
            string nombre = leerLinea("Nombre del curso: ");
            if (nombre.empty()) { cout << "Nombre invalido." << endl; break; }

            if (sis.curso != nullptr)
            {
                string conf = leerLinea("Ya existe un curso. Reemplazarlo? (s/n): ");
                if (conf != "s" && conf != "S") break;
                delete sis.curso;
                sis.curso = nullptr;
            }
            sis.curso = new NodoGenerico<string>(nombre);
            cout << "Curso '" << nombre << "' creado." << endl;
            break;
        }

        case 2:
        {
            if (sis.curso == nullptr) { cout << "No hay un curso. Cre" << "alo con la opcion 1." << endl; break; }

            cout << "\n--- Estructura actual ---" << endl;
            sis.curso->mostrar();

            string padre = leerLinea("\nNombre del nodo PADRE (un nodo que YA existe arriba): ");
            NodoGenerico<string> *n = sis.curso->buscar(padre);
            if (n == nullptr) { cout << "Nodo padre no encontrado en el arbol." << endl; break; }

            string hijo = leerLinea("Nombre del nuevo HIJO que se va a crear bajo '" + padre + "': ");
            if (hijo.empty()) { cout << "Nombre invalido." << endl; break; }

            n->agregarHijo(hijo);
            cout << "'" << hijo << "' agregado bajo '" << padre << "'." << endl;
            break;
        }

        case 3:
        {
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }

            cout << "\n--- Estructura actual ---" << endl;
            sis.curso->mostrar();

            string nodo = leerLinea("\nNombre de la hoja a eliminar: ");
            if (nodo == sis.curso->getValor())
            {
                cout << "No se puede eliminar la raiz desde aqui. Use la opcion 1 para reemplazarla." << endl;
                break;
            }
            if (sis.curso->eliminarHoja(nodo))
                cout << "Hoja eliminada." << endl;
            else
                cout << "No se encontro (puede que no exista o tenga hijos)." << endl;
            break;
        }

        case 4:
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }
            cout << "\n--- Estructura del curso ---" << endl;
            sis.curso->mostrar();
            break;

        case 5:
        {
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }
            cout << "\n--- Estructura actual ---" << endl;
            sis.curso->mostrar();
            string nodo = leerLinea("\nNombre del nodo a buscar: ");
            NodoGenerico<string> *n = sis.curso->buscar(nodo);
            if (n != nullptr)
                cout << "Encontrado: '" << n->getValor() << "' con "
                     << n->getHijos().size() << " hijo(s) directo(s)." << endl;
            else
                cout << "Nodo no encontrado." << endl;
            break;
        }

        case 6:
        {
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }
            cout << "\n--- Estructura actual ---" << endl;
            sis.curso->mostrar();
            string nodo = leerLinea("\nNombre del nodo: ");
            int nivel = sis.curso->nivel(nodo);
            if (nivel < 0) cout << "Nodo no encontrado." << endl;
            else            cout << "Nivel de '" << nodo << "': " << nivel
                                 << " (la raiz es nivel 0)." << endl;
            break;
        }

        case 7:
        {
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }
            cout << "\n--- Estructura actual ---" << endl;
            sis.curso->mostrar();
            string nodo = leerLinea("\nNombre del nodo: ");
            NodoGenerico<string> *n = sis.curso->buscar(nodo);
            if (n == nullptr) cout << "Nodo no encontrado." << endl;
            else              cout << "'" << nodo << "' tiene "
                                   << n->contarDescendientes() << " descendientes." << endl;
            break;
        }

        case 8:
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }
            cout << "Altura del arbol: " << sis.curso->altura() << endl;
            break;

        case 9:
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }
            cout << "\n--- Recursos hoja ---" << endl;
            sis.curso->mostrarHojas();
            break;

        case 10:
        {
            if (sis.curso == nullptr) { cout << "No hay un curso." << endl; break; }
            cout << "\n--- Estructura actual ---" << endl;
            sis.curso->mostrar();
            string nodo = leerLinea("\nNombre del nodo destino: ");
            vector<string> ruta;
            if (!sis.curso->rutaHasta(nodo, ruta))
            {
                cout << "Nodo no encontrado." << endl;
                break;
            }
            cout << "Ruta: ";
            for (size_t i = 0; i < ruta.size(); i++)
            {
                cout << ruta[i];
                if (i + 1 < ruta.size()) cout << " -> ";
            }
            cout << endl;
            break;
        }

        case 0:
            break;

        default:
            cout << "Opcion invalida." << endl;
        }
    } while (op != 0);
}
void menuNavegacion(Sistema &sis)
{
    if (sis.estudiantes.cantidad() == 0)
    {
        cout << "No hay estudiantes registrados. Registra uno primero en el menu de estudiantes." << endl;
        return;
    }

    string carne = leerLinea("Ingrese el carne del estudiante que va a navegar: ");
    Estudiante e;
    if (!sis.estudiantes.buscarPorCarne(carne, e))
    {
        cout << "Estudiante no encontrado." << endl;
        return;
    }

    cout << "Sesion iniciada para " << e.getNombre() << " (" << e.getCarne() << ")." << endl;

    // Obtiene/crea el historial asociado a este estudiante
    HistorialNavegacion &hist = sis.historiales[e.getCarne()];

    int op;
    do
    {
        cout << "\n--- Navegacion academica de " << e.getNombre() << " ---" << endl;
        cout << "1. Registrar visita a un nodo del curso" << endl;
        cout << "2. Mostrar historial de navegacion" << endl;
        cout << "3. Retroceder al elemento anterior" << endl;
        cout << "4. Limpiar historial" << endl;
        cout << "5. Registrar accion academica" << endl;
        cout << "6. Mostrar historial de acciones" << endl;
        cout << "7. Deshacer ultima accion" << endl;
        cout << "0. Volver" << endl;

        op = leerOpcion();

        switch (op)
        {
        case 1:
        {
            if (sis.curso == nullptr)
            {
                cout << "No hay curso cargado. Crealo en el menu de cursos." << endl;
                break;
            }
            cout << "\n--- Estructura del curso ---" << endl;
            sis.curso->mostrar();

            string nodo = leerLinea("\nNombre del nodo a visitar: ");
            if (nodo.empty()) { cout << "Nombre invalido." << endl; break; }
            if (sis.curso->buscar(nodo) == nullptr)
            {
                cout << "Ese nodo no existe en el curso." << endl;
                break;
            }
            hist.registrarVisita(nodo);
            cout << "Visita registrada: " << nodo << endl;
            break;
        }

        case 2:
            cout << "\n--- Historial de navegacion (mas reciente arriba) ---" << endl;
            hist.mostrarHistorial();
            break;

        case 3:
            if (!hist.hayHistorial())
            {
                cout << "No hay historial para retroceder." << endl;
                break;
            }
            cout << "Retrocedido. Se removio: " << hist.retroceder() << endl;
            break;

        case 4:
            hist.limpiarHistorial();
            cout << "Historial limpiado." << endl;
            break;

        case 5:
        {
            cout << "Tipo de accion:" << endl;
            cout << "  1. Inscripcion en una actividad" << endl;
            cout << "  2. Marcacion de recurso como completado" << endl;
            cout << "  3. Visita registrada por error" << endl;
            cout << "  4. Otro" << endl;
            string tipo    = leerLinea("Opcion (1-4): ");
            string detalle = leerLinea("Detalle (recurso o descripcion): ");
            if (detalle.empty()) { cout << "Detalle invalido." << endl; break; }

            string accion;
            if      (tipo == "1") accion = "Inscripcion: "      + detalle;
            else if (tipo == "2") accion = "Completado: "       + detalle;
            else if (tipo == "3") accion = "Visita por error: " + detalle;
            else                  accion = "Otro: "             + detalle;

            hist.registrarAccion(accion);
            cout << "Accion registrada: " << accion << endl;
            break;
        }

        case 6:
            cout << "\n--- Historial de acciones (mas reciente arriba) ---" << endl;
            hist.mostrarAcciones();
            break;

        case 7:
            if (!hist.hayAcciones())
            {
                cout << "No hay acciones para deshacer." << endl;
                break;
            }
            cout << "Deshecho: " << hist.deshacerAccion() << endl;
            break;

        case 0:
            break;

        default:
            cout << "Opcion invalida." << endl;
        }
    } while (op != 0);
}
void menuSolicitudes(Sistema &)   { cout << "(pendiente)" << endl; }
void menuIndice(Sistema &)        { cout << "(pendiente)" << endl; }
void menuReportes(Sistema &)      { cout << "(pendiente)" << endl; }
void guardarDatos(Sistema &sis)
{
    bool ok1 = Persistencia::guardarEstudiantes(sis.estudiantes, "data/estudiantes.txt");
    bool ok2 = Persistencia::guardarCurso(sis.curso,            "data/cursos.txt");
    bool ok3 = Persistencia::guardarSolicitudes(sis.solicitudes,"data/solicitudes.txt");

    cout << "\n--- Resultado de guardar ---" << endl;
    cout << "  Estudiantes:  " << (ok1 ? "OK" : "ERROR") << " (" << sis.estudiantes.cantidad() << ")" << endl;
    cout << "  Curso:        " << (ok2 ? "OK" : "ERROR") << endl;
    cout << "  Solicitudes:  " << (ok3 ? "OK" : "ERROR") << " (" << sis.solicitudes.cantidadPendientes() << ")" << endl;
    if (ok1 && ok2 && ok3)
        cout << "Todos los datos fueron guardados en data/." << endl;
}

void cargarDatos(Sistema &sis)
{
    bool okE = Persistencia::cargarEstudiantes(sis.estudiantes, "data/estudiantes.txt");

    NodoGenerico<string> *nuevoCurso = Persistencia::cargarCurso("data/cursos.txt");
    bool okC = (nuevoCurso != nullptr);
    if (okC)
    {
        if (sis.curso != nullptr) delete sis.curso;
        sis.curso = nuevoCurso;
    }

    bool okS = Persistencia::cargarSolicitudes(sis.solicitudes, "data/solicitudes.txt");

    cout << "\n--- Resultado de cargar ---" << endl;
    cout << "  Estudiantes:  " << (okE ? "OK" : "no encontrado") << " (" << sis.estudiantes.cantidad() << " en total)" << endl;
    cout << "  Curso:        " << (okC ? "OK" : "no encontrado") << endl;
    cout << "  Solicitudes:  " << (okS ? "OK" : "no encontrado") << " (" << sis.solicitudes.cantidadPendientes() << " pendientes)" << endl;
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
