#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED
#define archivoAlumnos "Alumnos.bin"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned long int gde;

typedef struct
{
    char calle[40];
    int numCalle;
    int piso;
    char dpto[4];
} stDir;

typedef struct
{
    char pais[50];
    char provincia[50];
    char ciudad[50];
} stPais;

typedef struct
{
    int primerParcial;
    int segundoParcial;
} stNotas;

typedef struct
{
    char materia[40];
    int anioMat;
    stNotas notas; // Arreglo para cargar notas de alumnos para parciales. Nota final sera el promedio de cuantas notas haya.
} stMateria;

typedef struct
{
    int matricula; // Matricula/Legajo de alumno.
    char nombre[50]; // Nombres del alumno.
    char apellido[50]; // Apellidos del alumno.
    char genero; // m - f - b.
    char password[50]; //en un principio es el dni, luego se puede modificar

    char mail[50]; // mail usado para acceder al sistema.

    gde dni; // DNI o Pasaporte.
    gde numCel; // numero celular.

    int edad; // edad del alumno.
    int anio; // año que cursa, si no esta del todo claro se pondra el año de la materia mas grande que curse.

    stDir dir; // direccion.
    stPais locacion; // lugar geografico donde se hospeda el alumno.

    stMateria matCursadas[5]; // materias que cursa.
    int valMaterias;

    int validacion; // validacion sirve para saber si el alumno esta de baja. No se muestra nunca esta parte, solo se compara para ver si el alumno esta o no en el archivo.
} stAlumno;

int verificarDatoUnicoRepetidoAlumnos(int matricula, gde dni);
stAlumno cargarAlumno();
void mostrarAlumno(stAlumno a);
void mostrarAlumnoListaApellidoLegajo(stAlumno a);

void cargarAlumnoInformacionGeneral(stAlumno * a);
void cargarAlumnoInformacionCursada(stAlumno * a);
void cargarAlumnoInformacionDireccion(stAlumno * a);
void cargarAlumnoInformacionLocacion(stAlumno * a);

void mostrarAlumnoInformacionGeneral(stAlumno a);
void mostrarAlumnoDireccion(stAlumno a);
void mostrarAlumnoLocacion(stAlumno a);
void mostrarAlumnoContactos(stAlumno a);
void mostrarAlumnoCursada(stAlumno a);

void cargarArchivoAlumnos(stAlumno a);
stAlumno * cargarArchivoEnArregloDinamico(int * cant);
int contarArchivo();
int contarAlumnosActivos();

void listarPorNombreMenorAMayor();
void ordenarPorInsercionNombreMenor(stAlumno a[], int val);
void listarPorNombreMayorAMenor();
void ordenarPorInsercionNombreMayor(stAlumno a[], int val);
void mostrarAlumnoListaNombre(stAlumno a);

void listarPorApellidoMenorAMayor();
void ordenarPorInsercionApellidoMenor(stAlumno a[], int val);
void listarPorApellidoMayorAMenor();
void ordenarPorInsercionApellidoMayor(stAlumno a[], int val);
void mostrarAlumnoListaApellido(stAlumno a);

void listarPorEdadMenorAMayor();
void ordenarPorInsercionEdadMenor(stAlumno a[], int val);
void listarPorEdadMayorAMenor();
void ordenarPorInsercionEdadMayor(stAlumno a[], int val);
void mostrarAlumnoListaEdad(stAlumno a);

int prioridadGenero(char genero);
void listarPorGenero();
void ordenarPorInsercionGenero(stAlumno a[], int val);
void mostrarAlumnoListaGenero(stAlumno a);

void listarPorPaisMenorAMayor();
void ordenarPorInsercionPaisMenor(stAlumno a[], int val);
void listarPorPaisMayorAMenor();
void ordenarPorInsercionPaisMayor(stAlumno a[], int val);
void mostrarAlumnoListaPais(stAlumno a);

void listadoAlumnosArgentinos();
void listadoAlumnosExtranjeros();
void filtradoPorPais(char paisBuscado[]);

int bajaDeAlumnos(int matricula);
void ejecutarBajaAlumno();
int altaDeAlumnos(int matricula);
void ejecutarAltaAlumno();

int modificarNombreAlumno(int matricula, char nombreNuevo[]);
void ejecutarModificacionNombreAlumno();

int modificarApellidoAlumno(int matricula, char apellidoNuevo[]);
void ejecutarModificacionApellidoAlumno();

int modificarGeneroAlumno(int matricula, char generoNuevo);
void ejecutarModificacionGeneroAlumno();

int modificarMailAlumno(int matricula, char mailNuevo[]);
void ejecutarModificacionMailAlumno();

int modificarDniAlumno(int matricula, gde dniNuevo);
void ejecutarModificacionDniAlumno();

int modificarCelularAlumno(int matricula, gde celularNuevo);
void ejecutarModificacionCelularAlumno();

int modificarEdadAlumno(int matricula, int edadNueva);
void ejecutarModificacionEdadAlumno();

int modificarAnioAlumno(int matricula, int anioNuevo);
void ejecutarModificacionAnioAlumno();

int modificarDireccionAlumno(int matricula, char calleNueva[], int numCalleNueva, int pisoNuevo, char dptoNuevo[]);
void ejecutarModificacionDireccionAlumno();

int modificarPaisAlumno(int matricula, char paisNuevo[], char provinciaNueva[], char ciudadNueva[]);
void ejecutarModificacionPaisAlumno();

void modificarMateriasCursadas();

void gestionarNotas();
int modificarNotasAlumno(int matricula);
void mostrarMateriasYnotas(stAlumno a);
void funcionModificarNotas(int control, stAlumno * aux);

void filtradoPorNombre();

void filtradoPorApellido();

void filtradoPorMatricula();
int pedirMatricula();

void filtradoPorRangoDeEdades();
void filtradoPorEdadMayoresA();
void filtradoPorEdadMenoresA();
int informacionRangoEdad();


void filtradoPorRangoDeNotas();
void filtradoPorNotasMayoresA();
void filtradoPorNotasMenoresA();
int informacionRangoNotas();
void mostrarNotasAlumnosPrimerParcial(stAlumno a, int u);
void mostrarNotasAlumnosSegundoParcial(stAlumno a, int u);

void filtradoPorGenero();
char pedirGenero();

void filtradoPorDadosDeBaja();

void mostrarMaterias(stAlumno a);
void materiasMostrarAalumno(int matricula);
void notasMostrarAalumno(int matricula);
void materiasAprobadasMostrarAalumno(int matricula);
void mostrarMateriasYnotasAalumnoAprobado(stAlumno a);
void consultaDeEstadoMostrarAalumno(int matricula);
void mostrarAlumnoEstado(stAlumno a);

void datosPersonalesMostrarAalumno(int matricula);

int verificarCambioPasswordAlumno(int matricula, char password[]);
int cambiarPasswordAlumno(int matricula, char password[]);
int ejecutarCambioPasswordAlumno(int matricula);

#endif // ALUMNO_H_INCLUDED
