#include <string.h>
#include "alumno.h"
#include <ctype.h>

///VERIFICACIONES
int verificarDatoUnicoRepetidoAlumnos(int matricula, gde dni){ //verifica si el dni o matricula del alumno cargado (campos unicos) ya existen
    FILE * buf=fopen(archivoAlumnos,"rb");
    int repetido=0;
    stAlumno aux;

    if(buf){
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && repetido==0){
            if(aux.matricula==matricula || aux.dni==dni){
                repetido=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return repetido;
}

int verificarInicioSesionAlumno(gde dni, char password[]){ //verifica si los datos ingresados son correctos
    FILE * buf=fopen(archivoAlumnos,"rb");
    stAlumno aux;
    int matriculaEnSesion=-1;

    if(buf){
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && matriculaEnSesion==-1){ //si no encontro un alumno y el archivo aun no termino, sigue buscando
            if(aux.dni==dni && strcmpi(aux.password,password)==0){
                matriculaEnSesion=aux.matricula;
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo\n");
    }


    return matriculaEnSesion; //retorna quien inicio sesion (la matricula)
}


void cargarAlumnoInformacionGeneral(stAlumno * a)
{
    while (getchar()!='\n');
    printf("Nombre: ");
    //fflush(stdin);
    gets(a->nombre);
    while (getchar()!='\n');
    printf("Apellido: ");
    gets(a->apellido);
    //while (getchar()!='\n');
    system("cls");

    printf("    ==== %s ====\n", a->nombre);

    printf("Matricula: ");
    scanf("%d", &a->matricula);
    while (getchar()!='\n');

    printf("Genero: ");
    scanf(" %c", &a->genero);
    while (getchar()!='\n');

    printf("Mail: ");
    gets(a->mail);

    printf("DNI: ");
    scanf("%lu", &a->dni);

    printf("Celular: ");
    scanf("%lu", &a->numCel);

    printf("Edad: ");
    scanf("%d", &a->edad);
}

void cargarAlumnoInformacionCursada(stAlumno * a)
{
    int i=0;
    char control='s';

    printf("\nCURSADA\n");

    printf("Anio que cursa (Si no esta bien definido: el anio de la materia mas avanzada): ");
    scanf("%d", &a->anio);
    while (getchar() != '\n');

    while (control=='s' && i<5)
    {
        printf("Materia que cursa: ");
        gets(a->matCursadas[i].materia);
        printf("Anio de la materia: ");
        scanf("%d", &a->matCursadas[i].anioMat);
        printf("Si quiere seguir cargando materias presione s. Recuerde que solo puede cargar 5 por alumno\n");
        scanf(" %c", &control);
        while(getchar()!='\n');
        a->valMaterias=a->valMaterias+1;

        i++;
        if (i==5)
        {
            printf("Ingreso el maximo de materias permitidas\n");
        }
        else
        {

        }
    }
}

void cargarAlumnoInformacionDireccion(stAlumno * a)
{
    printf("\nDIRECCION\n");

    printf("Calle: ");
    gets(a->dir.calle);

    printf("Numero: ");
    scanf("%d", &a->dir.numCalle);
    while (getchar() != '\n');

    printf("Piso: ");
    scanf("%d", &a->dir.piso);
    while (getchar() != '\n');

    printf("Departamento: ");
    gets(a->dir.dpto);

}

void cargarAlumnoInformacionLocacion(stAlumno * a)
{
    printf("\nLOCACION\n");

    printf("Pais: ");
    gets(a->locacion.pais);

    printf("Provincia: ");
    gets(a->locacion.provincia);

    printf("Ciudad: ");
    gets(a->locacion.ciudad);
}

stAlumno cargarAlumno()
{
    stAlumno a;

    a.valMaterias=0;

    cargarAlumnoInformacionGeneral(&a);

        a.validacion=-1;

        cargarAlumnoInformacionCursada(&a);

        cargarAlumnoInformacionDireccion(&a);

        cargarAlumnoInformacionLocacion(&a);

        sprintf(a.password, "%ld", a.dni);
        a.validacion = 1;

    return a;
}

void mostrarAlumnoContactos(stAlumno a)
{
    printf("\n == CONTACTOS ==\n");
    printf("  - Celular: %lu\n", a.numCel);
    printf("  - Mail: %s", a.mail);
}

void mostrarAlumnoLocacion(stAlumno a)
{
    printf("\n == LOCACION ==\n");
    printf("  - Pais: %s", a.locacion.pais);
    printf("  - Provincia: %s", a.locacion.provincia);
    printf("  - Ciudad: %s", a.locacion.ciudad);

}

void mostrarAlumnoInformacionGeneral(stAlumno a)
{
    printf("    ==== %s ====\n", a.nombre);

    printf("\n == INFORMACION GENERAL ==\n");

    printf("  - Apellido: %s", a.apellido);
    printf("  - Matricula: %d\n", a.matricula);
    printf("  - Edad: %d\n", a.edad);
    printf("  - DNI: %lu\n", a.dni);
}

void mostrarAlumnoDireccion(stAlumno a)
{
    printf("\n == DIRECCION ==\n");
    printf("  - Calle: %s", a.dir.calle);
    printf("  - Numero: %d", a.dir.numCalle);
    printf("  - Piso: %d", a.dir.piso);
    printf("  - Departamento: %s", a.dir.dpto);
}

void mostrarAlumnoCursada(stAlumno a)
{
    int i=0;

    printf("\n == INFORMACION DE CURSADA ==\n");
    printf("  - Anio: %d\n", a.anio);

    while(i<a.valMaterias)
    {
        printf("  - Materia: %s\n", a.matCursadas[i].materia);
        printf("  - Anio de la materia %s: %d\n", a.matCursadas[i].materia, a.matCursadas[i].anioMat);
        i++;
    }
}

void mostrarAlumno(stAlumno a)
{
    mostrarAlumnoInformacionGeneral(a);

    mostrarAlumnoDireccion(a);

    mostrarAlumnoLocacion(a);

    mostrarAlumnoContactos(a);

    mostrarAlumnoCursada(a);
}

void cargarArchivoAlumnos(stAlumno a)
{
    FILE * buf= fopen(archivoAlumnos,"ab");

    if(buf!=NULL)
    {
        fwrite(&a,sizeof(stAlumno),1,buf);
        fclose(buf);
    }
    else
    {
        printf("No se pudo abrir el archivo\n");
    }
}

stAlumno * cargarArchivoEnArregloDinamico(int * cant)
{
    FILE * buf=fopen(archivoAlumnos, "rb");
    stAlumno * a=NULL;
    *cant=0;

    if(buf!=NULL)
    {
        *cant=contarArchivo();
        a=(stAlumno*)malloc((*cant)*sizeof(stAlumno));
        int i=0;

        if(a!=NULL)
        {
            while(fread(&a[i],sizeof(stAlumno),1,buf)>0)
            {
                i++;
            }
        }

        fclose(buf);
    }
    else
    {
        printf("No pudo abrir el archivo\n");
    }

    return a;
}

///CONTADORES
int contarArchivo() //cuenta la cantidad de alumnos en el archivo
{
    FILE * buf= fopen(archivoAlumnos, "rb");
    int cant=0;
    if(buf!=NULL)
    {
        fseek(buf, 0, SEEK_END);
        cant=ftell(buf)/sizeof(stAlumno);
        fclose(buf);
    }
    return cant;
}

int contarAlumnosActivos(){ //cuenta la cantidad de alumnos activos en el sistema universitario
    FILE * buf=fopen(archivoAlumnos,"rb");
    int cant=0;

    if(buf){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)>0){
            if(aux.validacion==1){
                cant++;
            }
        }
        fclose(buf);
    }

    return cant;

}


///ORDENAMIENTOS Y LISTADOS
void ordenarPorInsercionNombreMenor(stAlumno a[], int val)
{
    for(int i = 1; i < val; i++)
    {
        stAlumno aux = a[i];
        int j = i - 1;

        while(j >= 0 && strcmp(a[j].nombre, aux.nombre) > 0)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void ordenarPorInsercionNombreMayor(stAlumno a[], int val)
{
    for(int i = 1; i < val; i++)
    {
        stAlumno aux = a[i];
        int j = i - 1;

        while(j >= 0 && strcmp(a[j].nombre, aux.nombre) < 0)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void mostrarAlumnoListaNombre(stAlumno a)
{
    printf("%s %s\n", a.nombre, a.apellido);
}

void listarPorNombreMenorAMayor()
{
    int cant;
    stAlumno * a= cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionNombreMenor(a, cant);

        printf("=== Alumnos ordenados de menor a mayor por nombre ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaNombre(a[u]);
            }
            u++;
        }
        free(a);
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
}

void listarPorNombreMayorAMenor()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionNombreMayor(a, cant);

        printf("=== Alumnos ordenados de mayor a menor por nombre ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaNombre(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

void ordenarPorInsercionApellidoMenor(stAlumno a[], int val)
{
    for(int i = 1; i < val; i++)
    {
        stAlumno aux = a[i];
        int j = i - 1;

        while(j >= 0 && strcmp(a[j].apellido, aux.apellido) > 0)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void ordenarPorInsercionApellidoMayor(stAlumno a[], int val)
{
    for(int i = 1; i < val; i++)
    {
        stAlumno aux = a[i];
        int j = i - 1;

        while(j >= 0 && strcmp(a[j].apellido, aux.apellido) < 0)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void mostrarAlumnoListaApellido(stAlumno a)
{
    printf("%s %s\n", a.apellido, a.nombre);
}

void listarPorApellidoMenorAMayor()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionApellidoMenor(a, cant);

        printf("=== Alumnos ordenados de menor a mayor por apellido ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaApellido(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

void listarPorApellidoMayorAMenor()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionApellidoMayor(a, cant);

        printf("=== Alumnos ordenados de mayor a menor por apellido ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaApellido(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

void ordenarPorInsercionEdadMayor(stAlumno a[], int val)
{
    for(int i = 1; i < val; i++)
    {
        stAlumno aux = a[i];
        int j = i - 1;

        while(j >= 0 && a[j].edad < aux.edad)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void ordenarPorInsercionEdadMenor(stAlumno a[], int val)
{
    for(int i = 1; i < val; i++)
    {
        stAlumno aux = a[i];
        int j = i - 1;

        while(j >= 0 && a[j].edad > aux.edad)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void mostrarAlumnoListaEdad(stAlumno a)
{
    printf("%d - %s %s\n", a.edad, a.apellido, a.nombre);
}

void listarPorEdadMenorAMayor()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionEdadMenor(a, cant);

        printf("=== Alumnos ordenados de menor a mayor por edad ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaEdad(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

void listarPorEdadMayorAMenor()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionEdadMayor(a, cant);

        printf("=== Alumnos ordenados de mayor a menor por edad ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaEdad(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

int prioridadGenero(char genero)
{
    genero = toupper(genero);

    switch(genero)
    {
        case 'F': return 1;
        case 'M': return 2;
        case 'B': return 3;
        default:  return 4;
    }
}

void mostrarAlumnoListaGenero(stAlumno a)
{
    printf("%c - %s %s\n", a.genero, a.apellido, a.nombre);
}

void ordenarPorInsercionGenero(stAlumno a[], int val)
{
    int i, j;
    stAlumno aux;

    for(i = 1; i < val; i++)
    {
        aux = a[i];
        j = i - 1;

        while(j >= 0 && prioridadGenero(a[j].genero) > prioridadGenero(aux.genero))
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void listarPorGenero()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionGenero(a, cant);

        printf("=== Alumnos ordenados por genero ===");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaGenero(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

void mostrarAlumnoListaPais(stAlumno a)
{
    printf("%s - %s %s\n", a.locacion.pais, a.apellido, a.nombre);
}

void ordenarPorInsercionPaisMenor(stAlumno a[], int val)
{
    int i, j;
    stAlumno aux;

    for(i = 1; i < val; i++)
    {
        aux = a[i];
        j = i - 1;

        while(j >= 0 && strcmp(a[j].locacion.pais, aux.locacion.pais) > 0)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void ordenarPorInsercionPaisMayor(stAlumno a[], int val)
{
    int i, j;
    stAlumno aux;

    for(i = 1; i < val; i++)
    {
        aux = a[i];
        j = i - 1;

        while(j >= 0 && strcmp(a[j].locacion.pais, aux.locacion.pais) < 0)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = aux;
    }
}

void listarPorPaisMenorAMayor()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionPaisMenor(a, cant);

        printf("=== Alumnos ordenados de menor a mayor por pais ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaPais(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

void listarPorPaisMayorAMenor()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        ordenarPorInsercionPaisMayor(a, cant);

        printf("=== Alumnos ordenados de mayor a menor por pais ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1)
            {
                mostrarAlumnoListaPais(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}


void listadoAlumnosArgentinos()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        printf("=== Alumnos Argentinos ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1 && strcmpi(a[u].locacion.pais,"Argentina")==0)
            {
                mostrarAlumnoListaPais(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}


void listadoAlumnosExtranjeros()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        printf("=== Alumnos Extranjeros ===\n\n");
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1 && strcmpi(a[u].locacion.pais,"Argentina")!=0)
            {
                mostrarAlumnoListaPais(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("El arreglo no tiene carga correcta\n");
    }
    free(a);
}

void filtradoPorPais(char paisBuscado[])
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);

    if(a!=NULL)
    {
        printf("=== Alumnos de %s ===\n\n", paisBuscado);
        int u=0;
        while(u<cant)
        {
            if(a[u].validacion==1 && strcmpi(a[u].locacion.pais,paisBuscado)==0)
            {
                mostrarAlumnoListaPais(a[u]);
            }
            u++;
        }
    }
    else
    {
        printf("No se pudo abrir el archivo\n");
    }
    free(a);
}


///BAJA Y ALTA
int bajaDeAlumnos(int matricula){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){
                if(aux.validacion==0){
                    modificado=2; //el alumno ya estaba dado de baja
                }else{
                    aux.validacion=0; //guarda el valor en 0 (dado de baja)

                    fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR); //(vuelve un lugar atras a partir de la posicion actual)
                    fwrite(&aux,sizeof(stAlumno),1,buf); //sobreescribe todo el struct, pero unicamente con el valor de validacion cambiado

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

void ejecutarBajaAlumno(){
    int matricula=0;
    int modificado=0;

    printf("Escriba la matricula del alumno que desea dar de BAJA: \n");
    scanf("%d", &matricula);

    modificado=bajaDeAlumnos(matricula);

    if(modificado==1){
        printf("El alumno con matricula %d fue dado de baja.\n", matricula);
    }else if(modificado==2){
        printf("El alumno con matricula %d ya se encontraba dado de baja.\n", matricula);
    }else{
        printf("No se encontro al alumno con matricula %d.\n", matricula);
    }
}

int altaDeAlumnos(int matricula){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){
                if(aux.validacion==1){
                    modificado=2; //el alumno ya estaba dado de alta
                }else{
                    aux.validacion=1; //guarda el valor en 1 (dado de alta)

                    fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR); //(vuelve un lugar atras a partir de la posicion actual)
                    fwrite(&aux,sizeof(stAlumno),1,buf); //sobreescribe todo el struct, pero unicamente con el valor de validacion cambiado

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

void ejecutarAltaAlumno(){
    int matricula=0;
    int modificado=0;

    printf("Escriba la matricula del alumno que desea dar de ALTA: \n");
    scanf("%d", &matricula);

    modificado=altaDeAlumnos(matricula);

    if(modificado==1){
        printf("El alumno con matricula %d fue dado de alta.\n", matricula);
    }else if (modificado==2){
        printf("El alumno con matricula %d ya se encontraba dado de alta.\n", matricula);
    }else{
        printf("No se encontro al alumno con matricula %d.\n", matricula);
    }
}

///MODIFICACION DE DATOS

int modificarNombreAlumno(int matricula, char nombreNuevo[]){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                strcpy(aux.nombre,nombreNuevo);

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;
}

void ejecutarModificacionNombreAlumno(){
    int matricula=0;
    int modificado=0;
    char nombre[50];

    matricula=pedirMatricula();
    while(getchar()!='\n');
    printf("Escriba el nuevo nombre del alumno: \n");
    gets(nombre);
    modificado=modificarNombreAlumno(matricula,nombre);

    if(modificado==1){
        printf("El nombre del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }
}

int modificarApellidoAlumno(int matricula, char apellidoNuevo[]){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                strcpy(aux.apellido,apellidoNuevo);

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionApellidoAlumno(){
    int matricula=0;
    int modificado=0;
    char apellido[50];

    matricula=pedirMatricula();
    while(getchar()!='\n');
    printf("Escriba el nuevo apellido del alumno: \n");
    gets(apellido);
    modificado=modificarApellidoAlumno(matricula,apellido);

    if(modificado==1){
        printf("El apellido del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }

}

int modificarGeneroAlumno(int matricula, char generoNuevo){

    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                aux.genero=generoNuevo;

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionGeneroAlumno(){
    int modificado=0;
    int matricula=0;
    char genero;

    matricula=pedirMatricula();
    while(getchar()!='\n');
    printf("Escriba el nuevo genero del alumno: \n");
    scanf(" %c",&genero);
    modificado=modificarGeneroAlumno(matricula,genero);

    if(modificado==1){
        printf("El genero del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }

}

int modificarMailAlumno(int matricula, char mailNuevo[]){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                strcpy(aux.mail,mailNuevo);

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionMailAlumno(){
    int modificado=0;
    int matricula=0;
    char mail[50];

    matricula=pedirMatricula();
    while(getchar()!='\n');
    printf("Escriba el nuevo mail del alumno: \n");
    gets(mail);
    modificado=modificarMailAlumno(matricula,mail);

    if(modificado==1){
        printf("El mail del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }
}


int modificarDniAlumno(int matricula, gde dniNuevo){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                aux.dni=dniNuevo;

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionDniAlumno(){
    int modificado=0;
    int matricula=0;
    gde dni=0;

    matricula=pedirMatricula();
    printf("Escriba el nuevo DNI del alumno: \n");
    scanf("%ld",&dni);
    modificado=modificarDniAlumno(matricula,dni);

    if(modificado==1){
        printf("El DNI del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }

}

int modificarCelularAlumno(int matricula, gde celularNuevo){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                aux.numCel=celularNuevo;

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionCelularAlumno(){
    int modificado=0;
    int matricula=0;
    gde celular=0;

    matricula=pedirMatricula();
    printf("Escriba el nuevo celular del alumno: \n");
    scanf("%ld",&celular);
    modificado=modificarCelularAlumno(matricula,celular);

    if(modificado==1){
        printf("El celular del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }

}


int modificarEdadAlumno(int matricula, int edadNueva){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                aux.edad=edadNueva;

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionEdadAlumno(){
    int modificado=0;
    int matricula=0;
    int edad=0;

    matricula=pedirMatricula();
    printf("Escriba la nueva edad del alumno: \n");
    scanf("%d",&edad);
    modificado=modificarEdadAlumno(matricula,edad);

    if(modificado==1){
        printf("La edad del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }


}

int modificarAnioAlumno(int matricula, int anioNuevo){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                aux.anio=anioNuevo;

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionAnioAlumno(){
    int modificado=0;
    int matricula=0;
    int anio=0;

    matricula=pedirMatricula();
    printf("Escriba el nuevo año del alumno: \n");
    scanf("%d",&anio);
    modificado=modificarAnioAlumno(matricula,anio);

    if(modificado==1){
        printf("El año del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }

}

int modificarDireccionAlumno(int matricula, char calleNueva[], int numCalleNueva, int pisoNuevo, char dptoNuevo[]){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                strcpy(aux.dir.calle,calleNueva);
                aux.dir.numCalle=numCalleNueva;
                aux.dir.piso=pisoNuevo;
                strcpy(aux.dir.dpto,dptoNuevo);

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;

}

void ejecutarModificacionDireccionAlumno(){
    int modificado=0;
    int matricula=0;
    char calle[40];
    int numCalle=0;
    int piso=0;
    char dpto[4];

    matricula=pedirMatricula();
    while(getchar()!='\n');
    printf("Escriba la nueva calle del alumno: \n");
    gets(calle);
    printf("Escriba el nuevo numero de calle del alumno: \n");
    scanf("%d",&numCalle);
    printf("Escriba el nuevo piso del alumno: \n");
    scanf("%d",&piso);
    while(getchar()!='\n');
    printf("Escriba el nuevo dpto del alumno: \n");
    gets(dpto);
    modificado=modificarDireccionAlumno(matricula,calle,numCalle,piso,dpto);

    if(modificado==1){
        printf("La direccion del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }

}


int modificarPaisAlumno(int matricula, char paisNuevo[], char provinciaNueva[], char ciudadNueva[]){
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0){
            if(aux.matricula==matricula){ //encontro al usuario
                strcpy(aux.locacion.pais,paisNuevo);
                strcpy(aux.locacion.provincia,provinciaNueva);
                strcpy(aux.locacion.ciudad,ciudadNueva);

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

    return modificado;


}

void ejecutarModificacionPaisAlumno(){
    int modificado=0;
    int matricula=0;
    char pais[50];
    char provincia[50];
    char ciudad[50];

    matricula=pedirMatricula();
    while(getchar()!='\n');
    printf("Escriba el nuevo pais del alumno: \n");
    gets(pais);
    while(getchar()!='\n');
    printf("Escriba la nueva provincia del alumno: \n");
    gets(provincia);
    while(getchar()!='\n');
    printf("Escriba la nueva ciudad del alumno: \n");
    gets(ciudad);
    modificado=modificarPaisAlumno(matricula,pais,provincia,ciudad);

    if(modificado==1){
        printf("El pais del alumno con matricula %d se modifico correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }

}

void modificarMateriasCursadas()
{ //revisar
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;
    int control;
    char materiaNueva[30];
    int anioNuevo;
    int matricula=pedirMatricula();

    if(buf!=NULL){
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,buf)==1 && modificado==0)
        {
            if(aux.matricula==matricula)
            { //encontro al usuario
                mostrarMateriasYnotas(aux);

                printf("Ingrese el Id de la materia que quiere modificar: ");
                scanf("%d", &control);
                control--;

                printf("Ingrese el nuevo nombre de la materia: ");
                while(getchar()!='\n');
                gets(materiaNueva);

                printf("Ingrese el nuevo anio de la materia: ");
                scanf("%d", &anioNuevo);

                strcpy(aux.matCursadas[control].materia,materiaNueva);
                aux.matCursadas[control].anioMat=anioNuevo;

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);
                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fread(&aux,sizeof(stAlumno),1,buf);

                mostrarMateriasYnotas(aux);
                system("pause");

                modificado=1; //se modifico el campo y se corta la busqueda
            }
        }

        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo \n");
    }
}

void mostrarAlumnoListaApellidoLegajo(stAlumno a)
{
    printf("%d - %s %s\n", a.matricula , a.apellido, a.nombre);
}

void gestionarNotas()
{
    int cant;
    stAlumno * a = cargarArchivoEnArregloDinamico(&cant);
    int u=0;

    while(u<cant)
    {
        if(a[u].validacion==1)
        {
            mostrarAlumnoListaApellidoLegajo(a[u]);
        }
        u++;
    }

    int matricula=0;
    int modificado=0;

    printf("Escriba la matricula del alumno a cargar/modificar notas: \n");
    scanf("%d",&matricula);

    modificado=modificarNotasAlumno(matricula);

    if(modificado==1){
        printf("Las notas del alumno con matricula %d se modificaron correctamente. \n",matricula);
    }else{
        printf("No se encontro al alumno con matricula %d \n",matricula);
    }
    free(a);
}

void mostrarMateriasYnotas(stAlumno a)
{
    int i=0;
    printf("   === %s %s ===\n", a.apellido, a.nombre);
    printf("  Materias cursadas:\n");
    while(i<a.valMaterias)
    {
        printf("Id: %d - %s\n", i+1, a.matCursadas[i].materia);
        printf("Primer parcial: ");
        if(a.matCursadas[i].notas.primerParcial < 11 && a.matCursadas[i].notas.primerParcial > -1)
        {
            printf("%d",  a.matCursadas[i].notas.primerParcial);
        }
        printf("\n");
        printf("Segundo parcial: ");
        if(a.matCursadas[i].notas.segundoParcial < 11 && a.matCursadas[i].notas.segundoParcial > -1)
        {
            printf("%d", a.matCursadas[i].notas.segundoParcial);
        }
        printf("\n");

        i++;
    }
}

int modificarNotasAlumno(int matricula)
{
    FILE * buf=fopen(archivoAlumnos,"r+b");
    int modificado=0;

    if(buf!=NULL)
    {
        stAlumno aux;
        int control;
        char controlS='s';
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && modificado==0 && controlS=='s')
        {
            if(aux.matricula==matricula)
            {
                mostrarMateriasYnotas(aux);

                printf("Ingrese el Id de la materia que quiere modificar: ");
                scanf("%d", &control);
                control--;

                system("cls");

                if(control>=0 && control<aux.valMaterias)
                {
                    funcionModificarNotas(control, &aux);
                }
                else
                {
                    printf("Id de materia invalido\n");
                }

                printf("Si quiere seguir presione s\n");
                while(getchar()!='\n');
                scanf(" %c", &controlS);

                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);

                if(controlS!='s')
                {
                    modificado=1;
                }
            }
        }

        fclose(buf);
    }
    else
    {
        printf("No pudo abrir el archivo\n");
    }
    return modificado;
}

void funcionModificarNotas(int control, stAlumno * aux)
{
    int parar=1;
    while(parar==1)
    {
        printf("Ingrese la notas del primer parcial de %s (0-10): ", aux->matCursadas[control].materia);
        scanf("%d", &aux->matCursadas[control].notas.primerParcial);

        printf("Ingrese la nota del segundo parcial de %s (0-10): ", aux->matCursadas[control].materia);
        scanf("%d", &aux->matCursadas[control].notas.segundoParcial);

        if(aux->matCursadas[control].notas.primerParcial > 10 || aux->matCursadas[control].notas.primerParcial < 0)
        {
            printf("Nota invalida del primer parcial\n");
            parar=1;
        }
        else if(aux->matCursadas[control].notas.segundoParcial > 10 || aux->matCursadas[control].notas.segundoParcial < 0)
        {
            printf("Nota invalida del segundo parcial\n");
            parar=1;
        }
        else
        {
            parar=0;
        }

    }
}

/// FILTRADO POR NOMBRE

void filtradoPorNombre()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;
    char nombre[50];

    printf("Ingrese el nombre para filtrar: ");
    while(getchar()!='\n');
    gets(nombre);

    while(i<cant)
    {
        if(a[i].validacion==1)
        {
            if(strstr(a[i].nombre,nombre)!=NULL)
            {
                mostrarAlumnoListaNombre(a[i]);
            }
        }
        i++;
    }
}

/// FILTRADO POR APELLIDO

void filtradoPorApellido()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;
    char apellido[50];

    printf("Ingrese el apellido para filtrar: ");
    while(getchar()!='\n');
    gets(apellido);

    while(i<cant)
    {
        if(a[i].validacion==1)
        {
            if(strstr(a[i].apellido,apellido)!=NULL)
            {
                mostrarAlumnoListaApellido(a[i]);
            }
        }
        i++;
    }
}

/// FILTRADO POR MATRICULA

int pedirMatricula()
{
    int matricula;
    printf("Ingrese la matricula del alumno: ");
    scanf("%d", &matricula);

    return matricula;
}

void filtradoPorMatricula()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    int matricula=pedirMatricula();

    while(i<cant)
    {
        if(a[i].matricula==matricula)
        {
            mostrarAlumno(a[i]);
        }
        i++;
    }

}

/// FILTRADO POR EDADES
int informacionRangoEdad()
{
    int e;
    printf("Ingrese edad para filtrar: ");
    scanf("%d", &e);

    return e;
}

void filtradoPorRangoDeEdades()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    printf("Primer edad: \n");
    int edad1=informacionRangoEdad();
    printf("Segunda edad: \n");
    int edad2=informacionRangoEdad();

    if(edad1>edad2)
    {
        int aux;
        aux=edad1;
        edad1=edad2;
        edad2=aux;
    }

    ordenarPorInsercionEdadMenor(a, cant);

    while(i<cant)
    {
        if(a[i].validacion==1 && a[i].edad<=edad2 && a[i].edad>=edad1)
        {
            mostrarAlumnoListaEdad(a[i]);
        }
        i++;
    }
}

void filtradoPorEdadMayoresA()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    int edad=informacionRangoEdad();

    ordenarPorInsercionEdadMenor(a, cant);

    while(i<cant)
    {
        if(a[i].validacion==1 && a[i].edad > edad)
        {
            mostrarAlumnoListaEdad(a[i]);
        }
        i++;
    }
}

void filtradoPorEdadMenoresA()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    int edad=informacionRangoEdad();

    ordenarPorInsercionEdadMenor(a,cant);

    while(i<cant)
    {
        if(a[i].validacion==1 && a[i].edad < edad)
        {
            mostrarAlumnoListaEdad(a[i]);
        }
        i++;
    }
}

///FILTRADO POR NOTAS
void mostrarNotasAlumnosPrimerParcial(stAlumno a, int u)
{
    printf("Primer Parcial - %s %s - Nota: %d \n", a.apellido, a.nombre, a.matCursadas[u].notas.primerParcial);
}

void mostrarNotasAlumnosSegundoParcial(stAlumno a, int u)
{
    printf("Segundo Parcial - %s %s - Nota: %d \n", a.apellido, a.nombre, a.matCursadas[u].notas.segundoParcial);
}

int informacionRangoNotas()
{
    int n;
    printf(" Nota para filtrar: \n");
    scanf("%d", &n);

    return n;
}

void filtradoPorRangoDeNotas()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    printf("Primer");
    int nota1=informacionRangoNotas();
    printf("Segunda");
    int nota2=informacionRangoNotas();

    system("cls");

    if(nota1>nota2)
    {
        int aux=nota1;
        nota1=nota2;
        nota2=aux;
    }

    ordenarPorInsercionApellidoMenor(a, cant);

    while(i<cant)
    {
        int u=0;
        if(a[i].validacion == 1)
        {
            while(u < a[i].valMaterias)
            {
                if(a[i].matCursadas[u].notas.primerParcial >= nota1 && a[i].matCursadas[u].notas.primerParcial <= nota2)
                {
                    mostrarNotasAlumnosPrimerParcial(a[i], u);
                }
                if(a[i].matCursadas[u].notas.segundoParcial >= nota1 && a[i].matCursadas[u].notas.segundoParcial <= nota2)
                {
                    mostrarNotasAlumnosSegundoParcial(a[i], u);
                }

                u++;
            }
        }
        i++;
    }
}

void filtradoPorNotasMayoresA()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    int nota=informacionRangoNotas();

    system("cls");

    ordenarPorInsercionApellidoMenor(a, cant);

    while(i<cant)
    {
        int u=0;
        if(a[i].validacion==1)
        {
            while(u<a[i].valMaterias)
            {
                if(a[i].matCursadas[u].notas.primerParcial > nota)
                {
                    mostrarNotasAlumnosPrimerParcial(a[i], u);
                }
                if(a[i].matCursadas[u].notas.segundoParcial > nota)
                {
                    mostrarNotasAlumnosSegundoParcial(a[i], u);
                }
                u++;
            }
        }
        i++;
    }
}

void filtradoPorNotasMenoresA()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    int nota=informacionRangoNotas();

    system("cls");

    ordenarPorInsercionApellidoMenor(a, cant);

    while(i<cant)
    {
        int u=0;
        if(a[i].validacion==1)
        {
            while(u<a[i].valMaterias)
            {
                if(a[i].matCursadas[u].notas.primerParcial < nota)
                {
                    mostrarNotasAlumnosPrimerParcial(a[i], u);
                }
                if(a[i].matCursadas[u].notas.segundoParcial < nota)
                {
                    mostrarNotasAlumnosSegundoParcial(a[i], u);
                }
                u++;
            }
        }
        i++;
    }
}

/// FILTRADO POR GENERO

char pedirGenero()
{
    char genero;

    printf("Ingrese el genero a buscar (g, m, b): ");
    while(getchar()!='\n');
    scanf(" %c", &genero);

    return genero;
}

void filtradoPorGenero()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;
    char genero;

    genero=pedirGenero();

    while(i<cant)
    {
        if(a[i].validacion==1 && a[i].genero==genero)
        {
            mostrarAlumnoListaGenero(a[i]);
        }
        i++;
    }
}

/// FILTRADO POR BAJAS

void filtradoPorDadosDeBaja()
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    while(i<cant)
    {
        if(a[i].validacion==0)
        {
            mostrarAlumnoListaApellido(a[i]);
        }
        i++;
    }
}
///MENU DE ALUMNOS
void mostrarMaterias(stAlumno a)
{
    int i=0;
    while(i<a.valMaterias)
    {
        printf("%d - %s\n", i+1, a.matCursadas[i].materia);
        i++;
    }
}

void materiasMostrarAalumno(int matricula)
{
    FILE * buf=fopen(archivoAlumnos, "rb");
    stAlumno aux;

    if(buf){
        int encontrado=0;
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && encontrado==0){
            if(aux.matricula==matricula){
                mostrarMaterias(aux);
                encontrado=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo\n");
    }
}

void mostrarMateriasYnotasAalumno(stAlumno a)
{
    int i=0;
    while(i<a.valMaterias)
    {
        printf("-  %s\n", a.matCursadas[i].materia);
        printf("Primer parcial: ");
        if(a.matCursadas[i].notas.primerParcial < 11 && a.matCursadas[i].notas.primerParcial > -1)
        {
            printf("%d",  a.matCursadas[i].notas.primerParcial);
        }
        printf("\n");
        printf("Segundo parcial: ");
        if(a.matCursadas[i].notas.segundoParcial < 11 && a.matCursadas[i].notas.segundoParcial > -1)
        {
            printf("%d", a.matCursadas[i].notas.segundoParcial);
        }
        printf("\n");

        i++;
    }
}

void notasMostrarAalumno(int matricula)
{
    FILE * buf=fopen(archivoAlumnos, "rb");
    stAlumno aux;

    if(buf){
        int encontrado=0;
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && encontrado==0){
            if(aux.matricula==matricula){
                mostrarMateriasYnotasAalumno(aux);
                encontrado=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo\n");
    }
}

void mostrarMateriasYnotasAalumnoAprobado(stAlumno a)
{
    int i=0;

    while(i<a.valMaterias)
    {
        if(a.matCursadas[i].notas.primerParcial>=6 && a.matCursadas[i].notas.segundoParcial >=6)
        {
            printf("-  %s\n", a.matCursadas[i].materia);
            printf("Primer parcial: ");
            if(a.matCursadas[i].notas.primerParcial < 11 && a.matCursadas[i].notas.primerParcial > -1)
            {
                printf("%d",  a.matCursadas[i].notas.primerParcial);
            }
            printf("\n");
            printf("Segundo parcial: ");
            if(a.matCursadas[i].notas.segundoParcial < 11 && a.matCursadas[i].notas.segundoParcial > -1)
            {
                printf("%d", a.matCursadas[i].notas.segundoParcial);
            }
            printf("\n");
        }
        i++;
    }

}

void materiasAprobadasMostrarAalumno(int matricula)
{
    FILE * buf=fopen(archivoAlumnos, "rb");
    stAlumno aux;

    if(buf){
        int encontrado=0;
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && encontrado==0){
            if(aux.matricula==matricula){
                mostrarMateriasYnotasAalumnoAprobado(aux);
                encontrado=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo\n");
    }
}

void datosPersonalesMostrarAalumno(int matricula)
{
    FILE * buf=fopen(archivoAlumnos, "rb");
    stAlumno aux;

    if(buf){
        int encontrado=0;
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && encontrado==0){
            if(aux.matricula==matricula){
                mostrarAlumno(aux);
                encontrado=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo\n");
    }
}

/*void mostrarAlumnoEstado(stAlumno a)
{
    printf(" === %s %s ===\n", a.apellido, a.nombre);
    if(a.validacion==1)
    {
        printf("  - Usted se encuentra validado de alta en la plataforma de la UTN y puede seguir cursando\n");
    }
    if(a.validacion!=1)
    {
        printf("  - Usted se encuentra validado de baja en la plataforma de la UTN y no puede seguir cursando\n");
    }
    printf(" - EQUIPO DIRECTIVO\n");
}

void consultaDeEstadoMostrarAalumno(int matricula)
{
    int cant;
    stAlumno * a=cargarArchivoEnArregloDinamico(&cant);
    int i=0;

    while(i<cant && a[i].matricula!=matricula)
    {
        i++;
    }

    if(a[i].matricula==matricula)
    {
        mostrarAlumnoEstado(a[i]);
    }
}
*/
void mostrarAlumnoEstado(stAlumno a)
{
    printf(" === %s %s ===\n", a.apellido, a.nombre);
    if(a.validacion==1)
    {
        printf("  - Usted se encuentra validado de alta en la plataforma de la UTN y puede seguir cursando\n");
    }
    if(a.validacion!=1)
    {
        printf("  - Usted se encuentra validado de baja en la plataforma de la UTN y no puede seguir cursando\n");
    }
    printf(" - EQUIPO DIRECTIVO\n");
}

void consultaDeEstadoMostrarAalumno(int matricula)
{
    FILE * buf=fopen(archivoAlumnos, "rb");
    stAlumno aux;

    if(buf){
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 ){
            if(aux.matricula==matricula){
                mostrarAlumnoEstado(aux);
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo\n");
    }
}
///CAMBIO DE CONTRASEÑA
int verificarCambioPasswordAlumno(int matricula, char password[]){ //verifica si la contraseña que puso el usuario es correcta
    FILE * buf=fopen(archivoAlumnos,"rb");
    int flag=-1;
    stAlumno aux;

    if(buf){
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && flag==-1){ //-1 es que no encontro la matricula (lo cual implicaria un error en el sistema ya que si pudo iniciar sesion deberia existir)
            if(aux.matricula==matricula){
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

int cambiarPasswordAlumno(int matricula, char password[]){ //modifica la contraseña en el archivo
    FILE * buf=fopen(archivoAlumnos, "r+b");
    stAlumno aux;
    int modificado=0;

    if(buf){
        while(fread(&aux,sizeof(stAlumno),1,buf)>0 && modificado==0){
            if(aux.matricula==matricula){
                strcpy(aux.password,password);
                fseek(buf,(-1)*sizeof(stAlumno),SEEK_CUR);
                fwrite(&aux,sizeof(stAlumno),1,buf);
                modificado=1;
            }
        }
        fclose(buf);
    }else{
        printf("No se pudo abrir el archivo\n");
    }

    return modificado;
}

int ejecutarCambioPasswordAlumno(int matricula){ //interactua con el usuario para que ingrese la nueva contraseña
    char password[30];
    int flag=0;
    int modificado=0;
    int reintentar=1;

    do{
        while(getchar()!='\n');
        printf("Escriba la contraseña actual: \n");
        gets(password);

        flag=verificarCambioPasswordAlumno(matricula,password);

        if(flag==1){ //contraseña correcta
            printf("Escriba la contraseña nueva: \n");
            gets(password);

            modificado=cambiarPasswordAlumno(matricula,password);
            reintentar=0;
        }else{
            printf("Contraseña incorrecta. Para intentar de nuevo presione 1 \n");
            scanf("%d",&reintentar);
        }
    }while(reintentar==1);

    return modificado;
}
