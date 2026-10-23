#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumno.h"
#include "administradores.h"

void menuDeFiltradoAdmins();
void mostrarAlertaOpcionIncorrecta();
void mostrarAlertaVolviendo();
void mostrarMenuInicioSesion();
void menuInicioSesion();
void menuInicioSesionComoAdmin();
void menuInicioSesionComoAlumno();
void mostrarMenuAdministrador();
void menuAdministrador(gde dni);
void mostrarMenuGestionDeAlumnos();
void menuGestionDeAlumnos();
void mostrarMenuGestionDeAdministradores();
void menuGestionDeAdministradores();
void mostrarMenuAjustesAdmin();
void menuAjustesAdmin(gde dni);
void mostrarMenuDeFiltrado();
void menuDeFiltrado();
void mostrarMenuDeFiltradoPorNotas();
void menuFiltradoPorNotas();
void mostrarMenuDeFiltradoPorEdad();
void menuFiltradoPorEdad();
void mostrarMenuDeFiltradoPorPais();
void menuFiltradoPorPais();
void mostrarMenuAlumno();
void menuAlumno(int matricula);
void mostrarMenuListadoDeAlumnos();
void menuListadoDeAlumnos();
void mostrarMenuListadoDeAdministradores();
void menuListadoDeAdministradores();
void mostrarMenuDeModificacionDeAlumnos();
void menuDeModificacionDeAlumnos();
void mostrarMenuDeModificacionDeAdmins();
void menuDeModificacionDeAdmins();
gde verificarInicioSesionAdmin(char mail[], char password[]);
int verificarInicioSesionAlumno(gde dni, char password[]);

#endif
