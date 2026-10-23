#include "menu.h"
#include <string.h>

///ALERTAS
void mostrarAlertaOpcionIncorrecta(){
    system("cls");
    printf("------------------------------------------------------------------------\n");
    printf("Opcion incorrecta. Seleccione otra. \n");
}

void mostrarAlertaVolviendo(){
    system("cls");
    printf("------------------------------------------------------------------------\n");
    printf("Volviendo... \n");
    printf("------------------------------------------------------------------------\n");
}

///INICIO DE SESION
void mostrarMenuInicioSesion(){
        printf("----------------------------INICIO DE SESION----------------------------\n");
        printf("[1] Iniciar sesion como administrador \n");
        printf("[2] Iniciar sesion como alumno \n");
        printf("[3] Cerrar el sistema \n");
        printf("Seleccione la opcion a la que desea acceder: \n");
}

void menuInicioSesion(){
    int opcion=0;

    do{
        system("cls");
        mostrarMenuInicioSesion();
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                menuInicioSesionComoAdmin();
                break;

            case 2:
                menuInicioSesionComoAlumno();
                break;

            case 3:
                printf("Cerrando el sistema... \n");
                break;

            default:
                printf("------------------------------------------------------------------------\n");
                printf("Valor incorrecto \n");
                break;
        }
    } while(opcion!=3);

}


void menuInicioSesionComoAdmin(){
    char mail[50];
    char password[30];
    int flag=0;
    int volver=0;
    gde dniEnSesion=-1;

    printf("----------------------------INICIO DE SESION COMO ADMINISTRADOR----------------------------\n");

    while(flag==0 && volver!=1){ //mientras no haya un inicio de sesion exitoso y mientras el usuario NO quiera volver, se ejecuta el while
        while(getchar()!='\n');
        printf("Escriba su mail: \n");
        gets(mail);

        //fflush(stdin);
        //while(getchar()!='\n');
        printf("Escriba la contrasenia: \n");
        gets(password);

        dniEnSesion=verificarInicioSesionAdmin(mail,password); //1=ingresa, 0=no ingresa

        if(dniEnSesion==-1){ //si los datos no son correctos, se avisa al usuario
            printf("------------------------------------------------------------------------\n");
            printf("Mail o contraseña incorrecta. Intente de nuevo. \n");
            printf("Si desea volver al menu principal presione 1: \n");
            scanf("%d",&volver);

            while(getchar()!='\n');
        }else{
            flag=1;
        }
    }

    if(volver==1){ //si el usuario quiere volver al menu principal, se ejecuta esto
        printf("------------------------------------------------------------------------\n");
        printf("Regresando... \n"); //vuelve automaticamente, ya que esta funcion la llame desde el menu principal
    }

    if(flag==1){ //si los datos son correcto, inicia sesion y aca deberia ir el otro menu
        printf("Inicio de sesion exitoso. Bienvenido al sistema. \n");
        menuAdministrador(dniEnSesion);
    }

}


void menuInicioSesionComoAlumno(){
    gde dni;
    char password[30]; //deberia ser el dni o numero de matricula, despues se deberia poder cambiar
    int matricula=-1;
    int volver=0;
    int flag=0;

    printf("----------------------------INICIO DE SESION COMO ALUMNO----------------------------\n");

    while(flag==0 && volver==0){
        printf("Escriba su DNI: \n");
        scanf("%ld",&dni);

        while(getchar()!='\n');
        printf("Escriba la contraseña: \n");
        gets(password);

        matricula=verificarInicioSesionAlumno(dni,password);

        if(matricula==-1){
            printf("------------------------------------------------------------------------\n");
            printf("DNI o contraseña incorrecta. Intente de nuevo. \n");
            printf("Si desea regresar al menu principal presione 1: \n");
            scanf("%d",&volver);

            while(getchar()!='\n');
        }else{
            flag=1; //1= entra al sistema, 0= no entra (por default esta en 0)
        }
    }

    if(volver==1){
        mostrarAlertaVolviendo();
    }

    if(flag==1){
        printf("Inicio de sesion exitoso. Bienvenido al sistema. \n");
        menuAlumno(matricula); //paso el legajo para q se mantenga durante todo el menu de alumnos y asi acceder a sus datos
    }


}

///MENU ADMINISTRADOR
void mostrarMenuAdministrador(){
        printf("----------------------------MENU DE ADMINISTRADOR----------------------------\n");
        printf("[1] Menu de gestion de alumnos \n");
        printf("[2] Menu de gestion de administradores \n");
        printf("[3] Ajustes \n");
        printf("[4] Cerrar sesion \n");
        printf("Seleccione una opcion: \n");
}

void menuAdministrador(gde dni){
    int opcion=0;

    do{
        mostrarMenuAdministrador();
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                system("cls");
                menuGestionDeAlumnos();
                break;
            case 2:
                system("cls");
                menuGestionDeAdministradores();
                break;
            case 3:
                system("cls");
                menuAjustesAdmin(dni);
                break;
            case 4:
                printf("------------------------------------------------------------------------\n");
                printf("Cerrando sesion... \n");
                printf("------------------------------------------------------------------------\n");
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=4);


}


void mostrarMenuGestionDeAlumnos(){
        printf("----------------------------MENU DE GESTION DE ALUMNOS----------------------------\n");
        printf("[1] Cargar nuevos alumnos \n");
        printf("[2] Mostrar un listado de los alumnos \n");
        printf("[3] Filtrar alumnos por campos \n");
        printf("[4] Modificar datos de alumnos \n");
        printf("[5] Dar de baja a un alumno \n"); //en esta funcion podemos usar una pila para deshacer
        printf("[6] Dar de alta a un alumno \n");
        printf("[7] Gestionar notas \n");
        printf("[8] Ver cantidad total de alumnos activos \n");
        printf("[9] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuGestionDeAlumnos(){
    int opcion=0;

    do{
        mostrarMenuGestionDeAlumnos();
        scanf("%d",&opcion);
        int activos=0;
        stAlumno a;

        switch(opcion){
            case 1:
                system("cls");
                a=cargarAlumno();
                cargarArchivoAlumnos(a);
                break;
            case 2:
                system("cls");
                menuListadoDeAlumnos();
                break;
            case 3:
                system("cls");
                menuDeFiltrado();
                break;
            case 4:
                system("cls");
                menuDeModificacionDeAlumnos();
                break;
            case 5:
                system("cls");
                ejecutarBajaAlumno();
                break;
            case 6:
                system("cls");
                ejecutarAltaAlumno();
                break;
            case 7:
                system("cls");
                gestionarNotas();
                break;
            case 8:
                system("cls");
                activos=contarAlumnosActivos();
                printf("Actualmente hay un total de %d alumnos activos en el sistema universitario\n",activos);
                break;
            case 9:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=9);

}


void mostrarMenuGestionDeAdministradores(){
        printf("----------------------------MENU DE GESTION DE ADMINISTRADORES----------------------------\n");
        printf("[1] Agregar nuevos administradores \n");
        printf("[2] Mostrar un listado de los administradores \n");
        printf("[3] Filtrar administradores por campos \n");
        printf("[4] Modificar datos de administradores \n");
        printf("[5] Dar de baja a un administrador \n");
        printf("[6] Dar de alta a un administrador\n");
        printf("[7] Ver cantidad total de administradores activos \n");
        printf("[8] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuGestionDeAdministradores(){
    int opcion=0;

    do{
        mostrarMenuGestionDeAdministradores();
        scanf("%d",&opcion);
        stAdmin admin;
        int activos=0;

        switch(opcion){
            case 1:
                system("cls");
                admin=cargarAdmin();
                if(admin.estado==-1){
                    printf("Ese administrador ya existe. \n");
                }else{
                    cargarArchivoAdmin(admin);
                }
                break;
            case 2:
                system("cls");
                menuListadoDeAdministradores();
                break;
            case 3:
                system("cls");
                menuDeFiltradoAdmins();
                break;
            case 4:
                system("cls");
                menuDeModificacionDeAdmins();
                break;
            case 5:
                system("cls");
                ejecutarBajaAdmins();
                break;
            case 6:
                system("cls");
                ejecutarAltaAdmins();
                break;
            case 7:
                system("cls");
                activos=contarAdministradoresActivos();
                printf("Hay un total de %d administradores activos en el sistema \n",activos);
                break;
            case 8:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=8);

}

void mostrarMenuAjustesAdmin(){
        printf("----------------------------MENU DE AJUSTES----------------------------\n");
        printf("[1] Cambiar contraseña \n");
        printf("[2] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuAjustesAdmin(gde dni){
    int opcion=0;

    do{
        mostrarMenuAjustesAdmin();
        scanf("%d",&opcion);
        int modificado=0;

        switch(opcion){
            case 1:
                modificado=ejecutarCambioPasswordAdmin(dni);
                if(modificado==1){
                    printf("Se modifico la contraseña correctamente. \n");
                }else{
                    printf("No se pudo modificar la contraseña. \n");
                }
                break;
            case 2:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=2);

}

///BUSQUEDAS FILTRADAS
void mostrarMenuDeFiltrado(){
        printf("----------------------------MENU DE BUSQUEDA FILTRADA DE ALUMNOS----------------------------\n");
        printf("[1] Filtrar por nombre \n");
        printf("[2] Filtrar por apellido \n");
        printf("[3] Filtrar por matricula \n");
        printf("[4] Filtrar por notas \n"); //filtrado por rango, por menores a, por mayores a
        printf("[5] Filtrar por edad \n"); //filtrado por rango, por menores a, por mayores a
        printf("[6] Filtrar por genero \n");
        printf("[7] Filtrar por pais \n"); //arg, extranjeros, pais especifico
        printf("[8] Filtrar por dados de baja \n");
        printf("[9] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuDeFiltrado(){
    int opcion=0;

    do{
        mostrarMenuDeFiltrado();
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                filtradoPorNombre();
                break;
            case 2:
                filtradoPorApellido();
                break;
            case 3:
                filtradoPorMatricula();
                break;
            case 4:
                system("cls");
                menuFiltradoPorNotas();
                break;
            case 5:
                system("cls");
                menuFiltradoPorEdad();
                break;
            case 6:
                filtradoPorGenero();
                break;
            case 7:
                system("cls");
                menuFiltradoPorPais();
                break;
            case 8:
                filtradoPorDadosDeBaja();
                break;
            case 9:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=9);
}

void mostrarMenuDeFiltradoPorNotas(){
        printf("----------------------------MENU DE BUSQUEDA FILTRADA DE ALUMNOS POR NOTAS----------------------------\n");
        printf("[1] Filtrar por rango \n");
        printf("[2] Filtrar por mayores a... \n");
        printf("[3] Filtrar por menores a... \n");
        printf("[4] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuFiltradoPorNotas(){
    int opcion=0;

    do{
        mostrarMenuDeFiltradoPorNotas();
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                filtradoPorRangoDeNotas();
                break;
            case 2:
                filtradoPorNotasMayoresA();
                break;
            case 3:
                filtradoPorNotasMenoresA();
                break;
            case 4:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=4);
}

void mostrarMenuDeFiltradoPorEdad(){
        printf("----------------------------MENU DE BUSQUEDA FILTRADA DE ALUMNOS POR EDAD----------------------------\n");
        printf("[1] Filtrar por rango \n");
        printf("[2] Filtrar por mayores a... \n");
        printf("[3] Filtrar por menores a... \n");
        printf("[4] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuFiltradoPorEdad(){
    int opcion=0;

    do{
        mostrarMenuDeFiltradoPorEdad();
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                filtradoPorRangoDeEdades();
                break;
            case 2:
                filtradoPorEdadMayoresA();
                break;
            case 3:
                filtradoPorEdadMenoresA();
                break;
            case 4:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=4);
}

void mostrarMenuDeFiltradoPorPais(){
        printf("----------------------------MENU DE BUSQUEDA FILTRADA DE ALUMNOS POR PAIS----------------------------\n");
        printf("[1] Filtrar por alumnos de Argentina \n");
        printf("[2] Filtrar por alumnos extranjeros \n");
        printf("[3] Filtrar por pais especifico \n");
        printf("[4] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuFiltradoPorPais(){
    int opcion=0;
    char paisBuscado[50];

    do{
        mostrarMenuDeFiltradoPorPais();
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                listadoAlumnosArgentinos();
                break;
            case 2:
                listadoAlumnosExtranjeros();
                break;
            case 3:
                printf("Ingrese el pais a buscar:\n");
                while(getchar()!='\n');
                gets(paisBuscado);
                filtradoPorPais(paisBuscado);
                break;
            case 4:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=4);
}

void mostrarMenuDeFiltradoAdmins(){
        printf("----------------------------MENU DE BUSQUEDA FILTRADA DE ADMINISTRADORES----------------------------\n");
        printf("[1] Filtrar por nombre \n");
        printf("[2] Filtrar por apellido \n");
        printf("[3] Filtrar por DNI \n");
        printf("[4] Filtrar por genero \n");
        printf("[5] Filtrar por dados de baja \n");
        printf("[6] Volver al menu anterior \n");
        printf("Seleccione una opcion: \n");
}

void menuDeFiltradoAdmins(){
    int opcion=0;

    do{
        mostrarMenuDeFiltradoAdmins();
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                filtradoPorNombreAdmins();
                break;
            case 2:
                filtradoPorApellidoAdmins();
                break;
            case 3:
                filtradoPorDniAdmins();
                break;
            case 4:
                filtradoPorGeneroAdmins();
                break;
            case 5:
                filtradoPorDadosDeBajaAdmins();
                break;
            case 6:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=6);

}


///LISTADOS
void mostrarMenuListadoDeAlumnos(){
        printf("----------------------------MENU DE LISTADO DE ALUMNOS----------------------------\n");
        printf("[1] Listar por nombre de menor a mayor \n");
        printf("[2] Listar por nombre de mayor a menor \n");
        printf("[3] Listar por apellido de menor a mayor \n");
        printf("[4] Listar por apellido de mayor a menor \n");
        printf("[5] Listar por edad de menor a mayor \n");
        printf("[6] Listar por edad de mayor a menor \n");
        printf("[7] Listar por genero \n");
        printf("[8] Listar por pais de menor a mayor \n");
        printf("[9] Listar por pais de mayor a menor \n");
        printf("[10] Volver al menu anterior \n");
}

void menuListadoDeAlumnos(){
    int opcion=0;

    do{
        mostrarMenuListadoDeAlumnos();
        printf("Seleccione una opcion: \n");
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                listarPorNombreMenorAMayor();
                break;
            case 2:
                listarPorNombreMayorAMenor();
                break;
            case 3:
                listarPorApellidoMenorAMayor();
                break;
            case 4:
                listarPorApellidoMayorAMenor();
                break;
            case 5:
                listarPorEdadMenorAMayor();
                break;
            case 6:
                listarPorEdadMayorAMenor();
                break;
            case 7:
                listarPorGenero();
                break;
            case 8:
                listarPorPaisMenorAMayor();
                break;
            case 9:
                listarPorPaisMayorAMenor();
                break;
            case 10:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=10);

}

void mostrarMenuListadoDeAdministradores(){
        printf("----------------------------MENU DE LISTADO DE ADMINISTRADORES----------------------------\n");
        printf("[1] Listar por nombre de menor a mayor \n");
        printf("[2] Listar por nombre de mayor a menor \n");
        printf("[3] Listar por apellido de menor a mayor \n");
        printf("[4] Listar por apellido de mayor a menor \n");
        printf("[5] Listar por DNI de mayor a menor \n");
        printf("[6] Listar por DNI de menor a mayor \n");
        printf("[7] Volver al menu anterior \n");

}

void menuListadoDeAdministradores(){
    int opcion=0;

    do{
        mostrarMenuListadoDeAdministradores();
        printf("Seleccione una opcion: \n");
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                listarAdminsPorNombreMenorAMayor();
                break;
            case 2:
                listarAdminsPorNombreMayorAMenor();
                break;
            case 3:
                listarAdminsPorApellidoMenorAMayor();
                break;
            case 4:
                listarAdminsPorApellidoMayorAMenor();
                break;
            case 5:
                listarAdminsPorDniMayorAMenor();
                break;
            case 6:
                listarAdminsPorDniMenorAMayor();
                break;
            case 7:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=7);

}
///MODIFICACION DE DATOS
void mostrarMenuDeModificacionDeAlumnos(){
        printf("----------------------------MENU DE MODIFICACION DE ALUMNOS----------------------------\n");
        printf("[1] Modificar nombre \n");
        printf("[2] Modificar apellido \n");
        printf("[3] Modificar genero \n");
        printf("[4] Modificar mail \n");
        printf("[5] Modificar DNI \n");
        printf("[6] Modificar numero de celular \n");
        printf("[7] Modificar edad \n");
        printf("[8] Modificar año \n");
        printf("[9] Modificar direccion \n");
        printf("[10] Modificar pais \n");
        printf("[11] Modificar materias cursadas \n");
        printf("[12] Volver al menu anterior \n");
}

void menuDeModificacionDeAlumnos(){
    int opcion=0;

    do{
        mostrarMenuDeModificacionDeAlumnos();
        printf("Seleccione una opcion: \n");
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                ejecutarModificacionNombreAlumno();
                break;
            case 2:
                ejecutarModificacionApellidoAlumno();
                break;
            case 3:
                ejecutarModificacionGeneroAlumno();
                break;
            case 4:
                ejecutarModificacionMailAlumno();
                break;
            case 5:
                ejecutarModificacionDniAlumno();
                break;
            case 6:
                ejecutarModificacionCelularAlumno();
                break;
            case 7:
                ejecutarModificacionEdadAlumno();
                break;
            case 8:
                ejecutarModificacionAnioAlumno();
                break;
            case 9:
                ejecutarModificacionDireccionAlumno();
                break;
            case 10:
                ejecutarModificacionPaisAlumno();
                break;
            case 11:
                modificarMateriasCursadas();
                break;
            case 12:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=12);

}

void mostrarMenuDeModificacionDeAdmins(){
        printf("----------------------------MENU DE MODIFICACION DE ADMINS----------------------------\n");
        printf("[1] Modificar nombre \n");
        printf("[2] Modificar apellido \n");
        printf("[3] Modificar genero \n");
        printf("[4] Modificar mail \n");
        printf("[5] Modificar DNI \n");
        printf("[6] Volver al menu anterior \n");
}

void menuDeModificacionDeAdmins(){
    int opcion=0;

    do{
        mostrarMenuDeModificacionDeAdmins();
        printf("Seleccione una opcion: \n");
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                ejecutarModificacionNombreAdmin();
                break;
            case 2:
                ejecutarModificacionApellidoAdmin();
                break;
            case 3:
                ejecutarModificacionGeneroAdmin();
                break;
            case 4:
                ejecutarModificacionMailAdmin();
                break;
            case 5:
                ejecutarModificacionDniAdmin();
                break;
            case 6:
                mostrarAlertaVolviendo();
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }

    } while(opcion!=6);

}


///MENU ALUMNOS
void mostrarMenuAlumno(){
        printf("----------------------------MENU DE ALUMNO----------------------------\n");
        printf("[1] Ver materias en curso \n");
        printf("[2] Ver notas \n");
        printf("[3] Materias aprobadas \n");
        printf("[4] Ver datos personales \n");
        printf("[5] Cambiar contraseña \n");
        printf("[6] Consultar estado \n"); //alumno regular o dado de baja
        printf("[7] Cerrar sesion \n");
}

void menuAlumno(int matricula){
    int opcion=0;

    do{
        mostrarMenuAlumno();
        printf("Seleccione una opcion: \n");
        scanf("%d",&opcion);
        int modificado=0;

        switch(opcion){
            case 1:
                materiasMostrarAalumno(matricula);
                break;
            case 2:
                notasMostrarAalumno(matricula);
                break;
            case 3:
                materiasAprobadasMostrarAalumno(matricula);
                break;
            case 4:
                datosPersonalesMostrarAalumno(matricula);
                break;
            case 5:
                modificado=ejecutarCambioPasswordAlumno(matricula);
                if(modificado==1){
                    printf("Se modifico la contraseña correctamente. \n");
                }else{
                    printf("No se pudo modificar la contraseña. \n");
                }
                break;
            case 6:
                consultaDeEstadoMostrarAalumno(matricula);
                break;
            case 7:
                printf("------------------------------------------------------------------------\n");
                printf("Cerrando sesion... \n");
                printf("------------------------------------------------------------------------\n");
                break;
            default:
                mostrarAlertaOpcionIncorrecta();
                break;
        }


    } while(opcion!=7);

}
