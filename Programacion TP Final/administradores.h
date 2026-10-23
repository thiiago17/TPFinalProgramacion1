#ifndef ADMINISTRADORES_H_INCLUDED
#define ADMINISTRADORES_H_INCLUDED
#define archivoAdmins "Admins.bin"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long int gde;

typedef struct{
    char nombre[30];
    char apellido[30];
    char password[30];
    gde dni;
    char mail[50]; // mail usado para acceder al sistema.
    char genero;
    int estado; //1=activo, 0=dado de baja
}stAdmin;

int verificarDatoUnicoRepetidoAdmins(gde dni);
stAdmin cargarAdmin();
void cargarArchivoAdmin(stAdmin admin);

int contarArchivoAdmins();
int contarAdministradoresActivos();

int bajaDeAdmins(gde dni);
void ejecutarBajaAdmins();
int altaDeAdmins(gde dni);
void ejecutarAltaAdmins();

stAdmin * cargarArchivoAdminsEnArregloDinamico(int cant);

void ordenarAdminsPorInsercionNombreMenor(stAdmin admin[], int val);
void ordenarAdminsPorInsercionNombreMayor(stAdmin admin[], int val);
void mostrarAdminListaNombre(stAdmin admin);
void mostrarArregloAdminsRecursivoNombre(stAdmin admin[], int cant, int i);
void listarAdminsPorNombreMenorAMayor();
void listarAdminsPorNombreMayorAMenor();

void ordenarAdminsPorInsercionApellidoMenor(stAdmin admin[], int val);
void ordenarAdminsPorInsercionApellidoMayor(stAdmin admin[], int val);
void mostrarAdminListaApellido(stAdmin admin);
void mostrarArregloAdminsRecursivoApellido(stAdmin admin[], int cant, int i);
void listarAdminsPorApellidoMenorAMayor();
void listarAdminsPorApellidoMayorAMenor();

void ordenarAdminsPorSeleccionDniMenor(stAdmin admin[], int val);
void ordenarAdminsPorSeleccionDniMayor(stAdmin admin[], int val);
void mostrarAdminListaDni(stAdmin admin);
void mostrarArregloAdminsRecursivoDni(stAdmin admin[], int cant, int i);
void listarAdminsPorDniMenorAMayor();
void listarAdminsPorDniMayorAMenor();

gde pedirDni();
int modificarNombreAdmin(gde dni, char nombreNuevo[]);
void ejecutarModificacionNombreAdmin();
int modificarApellidoAdmin(gde dni, char apellidoNuevo[]);
void ejecutarModificacionApellidoAdmin();
int modificarDniAdmin(gde dni, gde dniNuevo);
void ejecutarModificacionDniAdmin();
int modificarMailAdmin(gde dni, char mailNuevo[]);
void ejecutarModificacionMailAdmin();
int modificarGeneroAdmin(gde dni, char generoNuevo);
void ejecutarModificacionGeneroAdmin();

void filtradoPorNombreAdmins();
void filtradoPorApellidoAdmins();
void filtradoPorDniAdmins();
void mostrarAdminListaGenero(stAdmin admin);
void filtradoPorGeneroAdmins();
void filtradoPorDadosDeBajaAdmins();

int verificarCambioPasswordAdmin(gde dni, char password[]);
int cambiarPasswordAdmin(gde dni, char password[]);
int ejecutarCambioPasswordAdmin(gde dni);

#endif

