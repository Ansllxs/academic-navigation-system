# academic-navigation-system

Sistema academico en consola desarrollado en C++ para administrar estudiantes, cursos, contenidos educativos, navegacion academica y solicitudes pendientes, integrando listas, pilas, colas, arbol generico y arbol binario de busqueda.

## Estructura del proyecto

```
academic-navigation-system/
├── main.cpp
├── Estudiante.h / .cpp
├── ListaEstudiantes.h / .cpp
├── ABB.h                  (template, header-only)
├── ArbolGenerico.h        (template, header-only)
├── Pila.h                 (template, header-only)
├── Cola.h                 (template, header-only)
├── HistorialNavegacion.h / .cpp
├── Solicitud.h / .cpp
├── ColaSolicitudes.h / .cpp
├── Persistencia.h / .cpp
├── Reportes.h / .cpp
└── data/
    ├── estudiantes.txt
    ├── cursos.txt
    └── solicitudes.txt
```

## Compilacion

```
g++ -std=c++14 *.cpp -o programa
./programa
```

## Estructuras de datos usadas

| Estructura       | Donde se usa                               |
|------------------|--------------------------------------------|
| Lista            | Almacenamiento principal de estudiantes    |
| ABB              | Indice de estudiantes por carne            |
| Arbol generico   | Cursos -> unidades -> temas -> recursos    |
| Pila             | Historial de navegacion y deshacer accion  |
| Cola (con prio.) | Solicitudes pendientes de atencion         |
