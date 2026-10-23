#include "administradores.h"
#include "alumno.h"
#include <string.h>
#include <ctype.h>

///VERIFICACIONES
int verificarDatoUnicoRepetidoAdmins(gde dni){ //verifica si el dni del administrador cargado (campo unico) ya existe
    FILE * buf=fopen(archivoAdmins,"rb");
    int repetido=0;
    stAdmin aux;

    if(buf){
        while(fread(&aux,sizeof(stAdmin),1,buf)>0 && repetido==0){
            if(aux.dni==dni){
                repetido=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return repetido;
}

gde verificarInicioSesionAdmin(char mail[], char password[]){ //verifica si los datos ingresados son correctos
    FILE * buf=fopen(archivoAdmins,"rb");
    stAdmin aux;
    int flag=0;
    gde dniEnSesion=-1;

    if(buf){
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && flag==0){
            if(strcmp(aux.mail,mail)==0 && strcmpi(aux.password,password)==0 && aux.estado==1){
                dniEnSesion=aux.dni;
                flag=1;
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }


    return dniEnSesion;
}

///CARGA DE ADMINS
stAdmin cargarAdmin(){ //carga un admin y lo retorna
    stAdmin admin;
    int repetido=0;

    while(getchar()!='\n');
    printf("Nombre: \n");
    gets(admin.nombre);

    printf("Apellido: \n");
    //while(getchar()!='\n');
    gets(admin.apellido);

    printf("Mail: \n");
    gets(admin.mail);

    printf("Genero: \n");
    scanf(" %c",&admin.genero);
    while (getchar() != '\n');

    printf("DNI: \n");
    scanf("%ld",&admin.dni);
    while (getchar() != '\n');

    sprintf(admin.password, "%ld", admin.dni); //guarda el numero en la cadena de texto

    repetido=verificarDatoUnicoRepetidoAdmins(admin.dni);
    if(repetido==1){ //1=el dni ingresado ya estaba en el archivo, dato repetido
        admin.estado=-1;
    }else{
        admin.estado=1;
    }

    return admin;
}

void cargarArchivoAdmin(stAdmin admin){ //carga el admin enviado por parametro en el archivo
    FILE * buf=fopen(archivoAdmins,"ab");

    if(buf){
        fwrite(&admin,sizeof(stAdmin),1,buf);
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo");
    }

}

///CONTADORES
int contarArchivoAdmins(){ //cuenta los elementos del archivo de administradores y retorna la cantidad
    FILE * buf= fopen(archivoAdmins, "rb");
    int cant=0;

    if(buf!=NULL){
        fseek(buf, 0, SEEK_END);
        cant=ftell(buf)/sizeof(stAdmin);
        fclose(buf);
    }
    return cant;
}

int contarAdministradoresActivos(){ //cuenta cuantos administradores activos hay
    FILE * buf=fopen(archivoAdmins,"rb");
    int cant=0;

    if(buf){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)>0){
            if(aux.estado==1){
                cant++;
            }
        }
        fclose(buf);
    }

    return cant;
}

///BAJA Y ALTA
int bajaDeAdmins(gde dni){ //intenta modificar el valor del estado a 0 y retorna si se modifico o no.
    FILE * buf=fopen(archivoAdmins,"r+b");
    int modificado=0;

    if(buf){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && modificado==0){
            if(aux.dni==dni){
                if(aux.estado==0){
                    modificado=2; //el admin ya estaba dado de baja
                }else{
                    aux.estado=0; //guarda el valor en 0 (dado de baja)

                    fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR); //(vuelve un lugar atras a partir de la posicion actual)
                    fwrite(&aux,sizeof(stAdmin),1,buf); //sobreescribe todo el struct, pero unicamente con el valor de estado cambiado

                    modificado=1;
                }
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo");
    }

    return modificado;
}

void ejecutarBajaAdmins(){ //pregunta al usuario a quien debe dar de baja y luego informa si pudo o no.
    gde dni=0;
    int modificado=0;
    int activos=contarAdministradoresActivos();

    if(activos>3){
        printf("Escriba el DNI del administrador que desea dar de BAJA: \n");
        scanf("%ld", &dni);

        modificado=bajaDeAdmins(dni);

        if(modificado==1){
            printf("El administrador con DNI %ld fue dado de baja.\n", dni);
        }else if(modificado==2){
            printf("El administrador con DNI %ld ya se encontraba dado de baja.\n", dni);
        }else{
            printf("No se encontro al administrador con DNI %ld.\n", dni);
        }
    }else{
        printf("No se puede dar de baja a ningun administrador ya que hay menos de 3 o menos activos. ");
    }

}

int altaDeAdmins(gde dni){ //intenta modificar el valor del estado a 1 y retorna si se modifico o no.
    FILE * buf=fopen(archivoAdmins,"r+b");
    int modificado=0;

    if(buf){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && modificado==0){
            if(aux.dni==dni){
                if(aux.estado==1){
                    modificado=2; //el admin ya estaba dado de alta
                }else{
                    aux.estado=1; //guarda el valor en 1 (dado de alta)

                    fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR); //(vuelve un lugar atras a partir de la posicion actual)
                    fwrite(&aux,sizeof(stAdmin),1,buf); //sobreescribe todo el struct, pero unicamente con el valor de validacion cambiado

                    modificado=1;
                }

            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;
}

void ejecutarAltaAdmins(){ //pregunta al usuario a quien debe dar de alta y luego informa si pudo o no.
    gde dni=0;
    int modificado=0;

    printf("Escriba el DNI del administrador que desea dar de ALTA: \n");
    scanf("%ld", &dni);

    modificado=altaDeAdmins(dni);

    if(modificado==1){
        printf("El administrador con DNI %ld fue dado de alta.\n", dni);
    }else if (modificado==2){
        printf("El administrador con DNI %ld ya se encontraba dado de alta.\n", dni);
    }else{
        printf("No se encontro al administrador con DNI %ld.\n", dni);
    }
}

///LISTADOS
stAdmin * cargarArchivoAdminsEnArregloDinamico(int cant){ //carga un arreglo dinamico en base a la cantidad de administradores y lo retorna en forma de puntero
    FILE * buf=fopen(archivoAdmins,"rb");
    stAdmin * a=NULL;

    if(buf!=NULL){
        a=(stAdmin*)malloc((cant)*sizeof(stAdmin));
        int i=0;

        if(a!=NULL){
            while(fread(&a[i],sizeof(stAdmin),1,buf)>0){
                i++;
            }
        }

        fclose(buf);
    }
    else{
        printf("No pudo abrir el archivo\n");
    }

    return a;
}

//Listados por nombre
void ordenarAdminsPorInsercionNombreMenor(stAdmin admin[], int val){ //ordena por insercion el arreglo dinamico de administradores de MENOR a MAYOR segun su NOMBRE
    for(int i = 1; i < val; i++){
        stAdmin aux = admin[i];
        int j = i - 1;

        while(j >= 0 && strcmp(admin[j].nombre, aux.nombre) > 0){
            admin[j + 1] = admin[j];
            j--;
        }

        admin[j + 1] = aux;
    }
}

void ordenarAdminsPorInsercionNombreMayor(stAdmin admin[], int val){ //ordena por insercion el arreglo dinamico de administradores de MAYOR a MENOR segun su NOMBRE
    for(int i = 1; i < val; i++){
        stAdmin aux = admin[i];
        int j = i - 1;

        while(j >= 0 && strcmp(admin[j].nombre, aux.nombre) < 0){
            admin[j + 1] = admin[j];
            j--;
        }

        admin[j + 1] = aux;
    }
}

void mostrarAdminListaNombre(stAdmin admin){ //muestra el nombre y apellido del administrador que se le pasa por parametro
    printf("%s %s\n", admin.nombre, admin.apellido);
}

void mostrarArregloAdminsRecursivoNombre(stAdmin admin[], int cant, int i){ //recorre el arreglo de forma recursiva y muestra aquellos que esten activos
    if(cant != i){ //si NO recorrio todo el arreglo, entra al if, sino corta la recursion
        if(admin[i].estado==1){
            mostrarAdminListaNombre(admin[i]);
        }
        mostrarArregloAdminsRecursivoNombre(admin,cant,i+1);
    }
}



void listarAdminsPorNombreMenorAMayor(){ //llama al resto de funciones para mostrar todos los administradores de MENOR a MAYOR segun su NOMBRE
    int cant=contarArchivoAdmins();
    stAdmin * admin= cargarArchivoAdminsEnArregloDinamico(cant);

    if(admin!=NULL){
        ordenarAdminsPorInsercionNombreMenor(admin, cant);

        printf("=== Administradores ordenados de menor a mayor por NOMBRE ===\n\n");
        int u=0;

        mostrarArregloAdminsRecursivoNombre(admin,cant,u);

    }else{
        printf("El arreglo no tiene la carga correcta\n");
    }
    free(admin);
}

void listarAdminsPorNombreMayorAMenor(){ //llama al resto de funciones para mostrar todos los administradores de MAYOR a MENOR segun su NOMBRE
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);

    if(admin!=NULL){
        ordenarAdminsPorInsercionNombreMayor(admin, cant);

        printf("=== Administradores ordenados de mayor a menor por NOMBRE ===\n\n");
        int u=0;

        mostrarArregloAdminsRecursivoNombre(admin,cant,u);

    }else{
        printf("El arreglo no tiene la carga correcta\n");
    }
    free(admin);
}

//Listados por apellido
void ordenarAdminsPorInsercionApellidoMenor(stAdmin admin[], int val){ //ordena por insercion el arreglo dinamico de administradores de MENOR a MAYOR segun su APELLIDO
    for(int i = 1; i < val; i++){
        stAdmin aux = admin[i];
        int j = i - 1;

        while(j >= 0 && strcmp(admin[j].apellido, aux.apellido) > 0){
            admin[j + 1] = admin[j];
            j--;
        }

        admin[j + 1] = aux;
    }
}

void ordenarAdminsPorInsercionApellidoMayor(stAdmin admin[], int val){ //ordena por insercion el arreglo dinamico de administradores de MAYOR a MENOR segun su APELLIDO
    for(int i = 1; i < val; i++){
        stAdmin aux = admin[i];
        int j = i - 1;

        while(j >= 0 && strcmp(admin[j].apellido, aux.apellido) < 0){
            admin[j + 1] = admin[j];
            j--;
        }

        admin[j + 1] = aux;
    }
}

void mostrarAdminListaApellido(stAdmin admin){ //muestra el apellido y nombre del administrador que se le pasa por parametro
    printf("%s %s\n", admin.apellido, admin.nombre);
}

void mostrarArregloAdminsRecursivoApellido(stAdmin admin[], int cant, int i){ //recorre el arreglo de forma recursiva y muestra aquellos que esten activos
    if(cant != i){ //si NO recorrio todo el arreglo, entra al if, sino corta la recursion
        if(admin[i].estado==1){
            mostrarAdminListaApellido(admin[i]);
        }
        mostrarArregloAdminsRecursivoApellido(admin,cant,i+1);
    }
}


void listarAdminsPorApellidoMenorAMayor(){ //llama al resto de funciones para mostrar todos los administradores de MENOR a MAYOR segun su APELLIDO
    int cant=contarArchivoAdmins();
    stAdmin * admin= cargarArchivoAdminsEnArregloDinamico(cant);

    if(admin!=NULL){
        ordenarAdminsPorInsercionApellidoMenor(admin, cant);

        printf("=== Administradores ordenados de menor a mayor por APELLIDO ===\n\n");
        int u=0;

        mostrarArregloAdminsRecursivoApellido(admin,cant,u);

    }else{
        printf("El arreglo no tiene la carga correcta\n");
    }
    free(admin);
}

void listarAdminsPorApellidoMayorAMenor(){ //llama al resto de funciones para mostrar todos los administradores de MAYOR a MENOR segun su APELLIDO
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);

    if(admin!=NULL){
        ordenarAdminsPorInsercionApellidoMayor(admin, cant);

        printf("=== Administradores ordenados de mayor a menor por APELLIDO ===\n\n");
        int u=0;

        mostrarArregloAdminsRecursivoApellido(admin,cant,u);

    }else{
        printf("El arreglo no tiene la carga correcta\n");
    }
    free(admin);
}

//Listados por DNI
void ordenarAdminsPorSeleccionDniMenor(stAdmin admin[], int val){ //ordena por seleccion el arreglo dinamico de administradores de MENOR a MAYOR segun su DNI
    for(int i=0; i <val-1; i++){
        stAdmin aux =admin[i];
        int posMenor=i;

        for(int j=i + 1; j<val; j++){
            if(admin[j].dni < admin[posMenor].dni){
                posMenor=j; // guarda la posición del nuevo DNI más chico
            }
        }
        admin[i]=admin[posMenor];
        admin[posMenor]=aux;
    }
}

void ordenarAdminsPorSeleccionDniMayor(stAdmin admin[], int val){ //ordena por seleccion el arreglo dinamico de administradores de MAYOR a MENOR segun su DNI
    for(int i=0; i <val-1; i++){
        stAdmin aux =admin[i];
        int posMayor=i;

        for(int j=i + 1; j<val; j++){
            if(admin[j].dni > admin[posMayor].dni){
                posMayor=j; // guarda la posición del nuevo DNI más grande
            }
        }
        admin[i]=admin[posMayor];
        admin[posMayor]=aux;
    }
}

void mostrarAdminListaDni(stAdmin admin){ //muestra el DNI, apellido y nombre del administrador que se le pasa por parametro
    printf("%ld - %s %s\n",admin.dni, admin.apellido, admin.nombre);
}

void mostrarArregloAdminsRecursivoDni(stAdmin admin[], int cant, int i){ //recorre el arreglo de forma recursiva y muestra aquellos que esten activos
    if(cant != i){ //si NO recorrio todo el arreglo, entra al if, sino corta la recursion
        if(admin[i].estado==1){
            mostrarAdminListaDni(admin[i]);
        }
        mostrarArregloAdminsRecursivoDni(admin,cant,i+1);
    }

}


void listarAdminsPorDniMenorAMayor(){ //llama al resto de funciones para mostrar todos los administradores de MENOR a MAYOR segun su DNI
    int cant=contarArchivoAdmins();
    stAdmin * admin= cargarArchivoAdminsEnArregloDinamico(cant);

    if(admin!=NULL){
        ordenarAdminsPorSeleccionDniMenor(admin, cant);

        printf("=== Administradores ordenados de menor a mayor por DNI ===\n\n");
        int u=0;

        mostrarArregloAdminsRecursivoDni(admin,cant,u);

        free(admin);
    }else{
        printf("El arreglo no tiene la carga correcta\n");
    }


}

void listarAdminsPorDniMayorAMenor(){ //llama al resto de funciones para mostrar todos los administradores de MAYOR a MENOR segun su DNI
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);

    if(admin!=NULL){
        ordenarAdminsPorSeleccionDniMayor(admin, cant);

        printf("=== Administradores ordenados de mayor a menor por DNI ===\n\n");
        int u=0;

        mostrarArregloAdminsRecursivoDni(admin,cant,u);

        free(admin);
    }else{
        printf("El arreglo no tiene la carga correcta\n");
    }

}

///MODIFICACION DE DATOS
gde pedirDni(){ //pide al usuario el DNI del administrador a modificar. Se utiliza en todas las funciones de modificacion
    gde dni;
    printf("Ingrese el DNI del administrador que desea modificar: \n");
    scanf("%ld", &dni);

    return dni;
}

int modificarNombreAdmin(gde dni, char nombreNuevo[]){ //intenta modificar el dato y retorna si pudo o no
    FILE * buf=fopen(archivoAdmins,"r+b");
    int modificado=0;

    if(buf){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && modificado==0){
            if(aux.dni==dni){ //encontro al usuario
                strcpy(aux.nombre,nombreNuevo);

                fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR);
                fwrite(&aux,sizeof(stAdmin),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;
}

void ejecutarModificacionNombreAdmin(){ //pide al usuario el dato modificado y llama a la correspondiente. Luego informa si pudo o no.
    gde dni=0;
    int modificado=0;
    char nombre[30];

    dni=pedirDni();
    while(getchar() != '\n');
    printf("Escriba el nuevo nombre del administrador: \n");
    gets(nombre);
    modificado=modificarNombreAdmin(dni,nombre);

    if(modificado==1){
        printf("El nombre del administrador con DNI %ld se modifico correctamente. \n",dni);
    }else{
        printf("No se encontro al administrador con DNI %ld \n",dni);
    }
}

int modificarApellidoAdmin(gde dni, char apellidoNuevo[]){ //intenta modificar el dato y retorna si pudo o no
    FILE * buf=fopen(archivoAdmins,"r+b");
    int modificado=0;

    if(buf){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && modificado==0){
            if(aux.dni==dni){ //encontro al usuario
                strcpy(aux.apellido,apellidoNuevo);

                fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR);
                fwrite(&aux,sizeof(stAdmin),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;
}

void ejecutarModificacionApellidoAdmin(){ //pide al usuario el dato modificado y llama a la correspondiente. Luego informa si pudo o no.
    gde dni=0;
    int modificado=0;
    char apellido[30];

    dni=pedirDni();
    while(getchar()!='\n');
    printf("Escriba el nuevo apellido del administrador: \n");
    gets(apellido);
    modificado=modificarApellidoAdmin(dni,apellido);

    if(modificado==1){
        printf("El apellido del administrador con DNI %ld se modifico correctamente. \n",dni);
    }else{
        printf("No se encontro al administrador con DNI %ld \n",dni);
    }
}

int modificarDniAdmin(gde dni, gde dniNuevo){
    FILE * buf=fopen(archivoAdmins,"r+b");
    int modificado=0;

    if(buf){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && modificado==0){
            if(aux.dni==dni){ //encontro al usuario
                aux.dni=dniNuevo;

                fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR);
                fwrite(&aux,sizeof(stAdmin),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;
}

void ejecutarModificacionDniAdmin(){ //pide al usuario el dato modificado y llama a la correspondiente. Luego informa si pudo o no.
    gde dni=0;
    int modificado=0;
    gde dniNuevo=0;

    dni=pedirDni();
    printf("Escriba el nuevo DNI del administrador: \n");
    scanf("%ld",&dniNuevo);
    modificado=modificarDniAdmin(dni,dniNuevo);

    if(modificado==1){
        printf("El DNI del administrador que tenia el DNI %ld se modifico correctamente. \n",dni);
    }else{
        printf("No se encontro al administrador con DNI %ld \n",dni);
    }
}

int modificarMailAdmin(gde dni, char mailNuevo[]){ //intenta modificar el dato y retorna si pudo o no
    FILE * buf=fopen(archivoAdmins,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && modificado==0){
            if(aux.dni==dni){ //encontro al usuario
                strcpy(aux.mail,mailNuevo);

                fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR);
                fwrite(&aux,sizeof(stAdmin),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;
}

void ejecutarModificacionMailAdmin(){ //pide al usuario el dato modificado y llama a la correspondiente. Luego informa si pudo o no.
    gde dni=0;
    int modificado=0;
    char mail[50];

    dni=pedirDni();
    while(getchar()!='\n');
    printf("Escriba el nuevo mail del administrador: \n");
    gets(mail);
    modificado=modificarMailAdmin(dni,mail);

    if(modificado==1){
        printf("El mail del administrador con DNI %ld se modifico correctamente. \n",dni);
    }else{
        printf("No se encontro al administrador con DNI %ld \n",dni);
    }
}

int modificarGeneroAdmin(gde dni, char generoNuevo){
    FILE * buf=fopen(archivoAdmins,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAdmin aux;
        while(fread(&aux,sizeof(stAdmin),1,buf)==1 && modificado==0){
            if(aux.dni==dni){ //encontro al usuario
                aux.genero=generoNuevo;

                fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR);
                fwrite(&aux,sizeof(stAdmin),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;
}

void ejecutarModificacionGeneroAdmin(){ //pide al usuario el dato modificado y llama a la correspondiente. Luego informa si pudo o no.
    gde dni=0;
    int modificado=0;
    char genero;

    dni=pedirDni();
    while(getchar()!='\n');
    printf("Escriba el nuevo genero del administrador: \n");
    scanf("% c",&genero);
    modificado=modificarGeneroAdmin(dni,genero);

    if(modificado==1){
        printf("El genero del administrador con DNI %ld se modifico correctamente. \n",dni);
    }else{
        printf("No se encontro al administrador con DNI %ld \n",dni);
    }
}

///FILTRADO

//Filtrado por nombre
void filtradoPorNombreAdmins(){ //filtra y muestra los administradores que contengan las letras o nombre seleccionado
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);
    int i=0;
    char nombre[50];

    while(getchar()!='\n');
    printf("Ingrese el nombre para filtrar: \n");
    gets(nombre);

    while(i<cant){
        if(admin[i].estado==1){
            if(strstr(admin[i].nombre,nombre)!=NULL){
                mostrarAdminListaNombre(admin[i]);
            }
        }
        i++;
    }

    free(admin);
}

//Filtrado por apellido
void filtradoPorApellidoAdmins(){ //filtra y muestra los administradores que contengan las letras o apellido seleccionado
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);
    int i=0;
    char apellido[50];

    printf("Ingrese el apellido para filtrar: \n");
    while(getchar()!='\n');
    gets(apellido);

    while(i<cant){
        if(admin[i].estado==1){
            if(strstr(admin[i].apellido,apellido)!=NULL){
                mostrarAdminListaApellido(admin[i]);
            }
        }
        i++;
    }

    free(admin);
}

//Filtrado por DNI
void filtradoPorDniAdmins(){ //filtra y muestra al administrador con el dni seleccionado
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);
    int i=0;
    gde dni;

    printf("Ingrese el DNI para filtrar: \n");
    scanf("%ld",&dni);

    while(i<cant){
        if(admin[i].estado==1){
            if(admin[i].dni==dni){
                mostrarAdminListaDni(admin[i]);
            }
        }
        i++;
    }

    free(admin);
}

//Filtrado por genero
void mostrarAdminListaGenero(stAdmin admin){ //muestra el nombre y apellido del administrador que se le pasa por parametro
    printf(" %c - %s %s\n",admin.genero, admin.nombre, admin.apellido);
}

void filtradoPorGeneroAdmins(){ //filtra y muestra los administradores con el genero seleccionado
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);
    int i=0;
    char genero;

    genero=pedirGenero(); //creado en alumnos.c

    while(i<cant){
        if(admin[i].estado==1 && admin[i].genero==genero){
            mostrarAdminListaGenero(admin[i]);
        }
        i++;
    }

    free(admin);
}

//Filtrado por dados de baja
void filtradoPorDadosDeBajaAdmins(){ //filtra y muestra los administradores con estado 0 (dado de baja)
    int cant=contarArchivoAdmins();
    stAdmin * admin=cargarArchivoAdminsEnArregloDinamico(cant);
    int i=0;

    while(i<cant){
        if(admin[i].estado==0){
            mostrarAdminListaNombre(admin[i]);
        }
        i++;
    }
    free(admin);
}

///CAMBIO DE CONTRASEÑA
int verificarCambioPasswordAdmin(gde dni, char password[]){ //verifica si la contraseña que puso el usuario es correcta
    FILE * buf=fopen(archivoAdmins,"rb");
    int flag=-1;
    stAdmin aux;

    if(buf){
        while(fread(&aux,sizeof(stAdmin),1,buf)>0 && flag==-1){ //-1 es que no encontro el dni (lo cual implicaria un error en el sistema ya que si pudo iniciar sesion deberia existir)
            if(aux.dni==dni){
                if(strcmp(aux.password,password)==0){
                    flag=1;
                }else{
                    flag=0;
                }
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo. \n");
    }

    return flag;
}

int cambiarPasswordAdmin(gde dni, char password[]){ //modifica la contraseña en el archivo
    FILE * buf=fopen(archivoAdmins, "r+b");
    stAdmin aux;
    int modificado=0;

    if(buf){
        while(fread(&aux,sizeof(stAdmin),1,buf)>0 && modificado==0){
            if(aux.dni==dni){
                strcpy(aux.password,password);
                fseek(buf,(-1)*sizeof(stAdmin),SEEK_CUR);
                fwrite(&aux,sizeof(stAdmin),1,buf);
                modificado=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo");
    }

    return modificado;
}

int ejecutarCambioPasswordAdmin(gde dni){ //interactua con el usuario para que ingrese la nueva contraseña
    char password[30];
    int flag=0;
    int modificado=0;
    int reintentar=1;

    do{
        while(getchar()!='\n');
        printf("Escriba la contraseña actual: \n");
        gets(password);

        flag=verificarCambioPasswordAdmin(dni,password);

        if(flag==1){ //contraseña correcta
            printf("Escriba la contraseña nueva: \n");
            gets(password);

            modificado=cambiarPasswordAdmin(dni,password);
            reintentar=0;
        }else{
            printf("Contraseña incorrecta. Para intentar de nuevo presione 1 \n");
            scanf("%d",&reintentar);
        }
    } while(reintentar==1);

    return modificado;
}

