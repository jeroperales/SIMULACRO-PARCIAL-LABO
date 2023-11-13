#include <stdio.h>
#include <stdlib.h>
#include "string.h"

//ESTRUCTURAS
typedef struct personaje
{
    char nombreYapellido [30];
    int edad;
    int dni;
} personaje;

typedef struct nodoLista
{
    personaje dato;
    struct nodoLista* anterior;
    struct nodoLista* siguiente;
} nodoLista;

typedef struct Especie
{
    char nombreEspecie[20]; //vampiro, hombre lobo, hada, medium, cambia formas, humano
    int rankPeligrosidad; //1 el m�s peligroso, 6 el menos peligroso
    float promedioEdad; // 0
    nodoLista* personajes; //lista de personajes que pertencen a esta especie
} Especie;

typedef struct nodoArbol
{

    Especie dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;

} nodoArbol;

typedef struct
{
    char nombreEspecie[20]; //vampiro, hombre lobo, hada, medium, cambia formas, humano
    int rankPeligrosidad;
    char nombreYapellido [30];
    int edad;
    int dni;


} registroArchivo;



//PROTOTIPADO
int cargaEspecie(Especie arreglo[], int validos, int dim);
int verificaEspecie(Especie arreglo[], int validos, char nombreEspecie[]);
int verificaRango(Especie arreglo[], int validos, int rango);
nodoLista* crearListaPersonaje(nodoLista* lista);
nodoLista* agregarPpio (nodoLista* lista, nodoLista* nuevoNodo);
int alta (Especie arreglo[], int validos, int dim);
void mostrarArregloEspecie(Especie arreglo[], int validos);
void mostrarListaPersonajes(nodoLista* lista);
nodoArbol* inicArbol();
nodoArbol* pasarListaAArbol(Especie arreglo[], int validos);
nodoArbol* crearNodoArbol(Especie dato);
nodoArbol* insertar(nodoArbol* arbol, nodoArbol* nuevoNodo);
void pasarArregloAArchivo(char archivo[], Especie arreglo[], int validos);

int main()
{

    int dim = 6;
    int validos = 0;
    char opc = 's';

    Especie arregloEspecie[6];
    //PUNTO 1 CARGAR LISTA DENTRO DE ARREGLOS
    while (opc == 's')
    {
        validos = alta(arregloEspecie, validos, dim);
        printf("SI DESEA CONTINUAR INGRESE s \n");
        fflush(stdin);
        scanf("%c", &opc);

    }
    //PUNTO 2 MOSTRAR LISTA DENTRO DE ARREGLO
    mostrarArregloEspecie(arregloEspecie, validos);

    //PUNTO 3 PASAR UN PERSONAJE A ARBOL EN ORDEN DE RANKING DE PELIGROSIDAD
    nodoArbol* arbol = inicArbol();
    arbol = pasarListaAArbol(arregloEspecie, validos);
    printf("\n\n\n");
    printf("ARBOL:\n\n");
    inOrder(arbol);




    return 0;
}


int cargaEspecie(Especie arreglo[], int validos, int dim)
{
    Especie aux;
    int loop = 0;
    int flag = 0;

    printf("INGRESE NOMBRE DE ESPECIE \n");
    fflush(stdin);
    gets(aux.nombreEspecie);

    while (loop == 0)
    {
        printf("INGRESE RANGO DE PELIGROSIDAD 1-6\n");
        scanf("%i", &aux.rankPeligrosidad);

        flag = verificaRango(arreglo,validos, aux.rankPeligrosidad);

        if(aux.rankPeligrosidad <=6 && aux.rankPeligrosidad>=1 && flag != -1)
        {
            loop = 1;
        }
        else
        {
            printf("INGRESE NUMERO DENTRO DEL RANGO Y/O QUE NO EXISTA PREVIAMENTE\n")
            ;
        }
    }

    aux.promedioEdad = 0;
    strcpy(arreglo[validos].nombreEspecie,aux.nombreEspecie);
    arreglo[validos].rankPeligrosidad = aux.rankPeligrosidad;
    arreglo[validos].personajes = NULL;


    validos = validos + 1;
    return validos;
}

int verificaRango(Especie arreglo[], int validos, int rango)
{
    int i = 0;
    int flag;

    while (i<validos)
    {
        if (arreglo[i].rankPeligrosidad == rango)
        {
            flag = -1;
        }
        i++;
    }


    return flag;
}




int verificaEspecie(Especie arreglo[], int validos, char nombre[])
{
    int i = 0;
    int flag = -1;
    while(i <=validos)
    {
        if (strcmp(arreglo[i].nombreEspecie, nombre)== 0)
        {
            flag = i;
        }

        i++;
    }

    return flag;
}


personaje crearPersonaje ()
{
    personaje aux;
    printf("INGRESE NOMBRE DE PERSONAJE \n");
    fflush(stdin);
    gets(aux.nombreYapellido);

    printf("INGRESE DNI DE PERSONAJE \n");
    scanf("%i", &aux.dni);

    printf("INGRESE EDAD DE PERSONAJE \n");
    scanf("%i", &aux.edad);

    return aux;
}

nodoLista* inicLista()
{
    return NULL;
}

nodoLista* crearNodoPersonaje (personaje dato)
{
    nodoLista* aux = (nodoLista*)malloc(sizeof(nodoLista));
    aux->dato = dato;
    aux->anterior = NULL;
    aux->siguiente = NULL;

    return aux;
}


int alta(Especie arreglo[], int validos, int dim)
{
    char nombre[20];
    int flag = 0;
    int i = 0;
    int posi;
    nodoLista* lista = NULL;

    printf("INGRESE NOMBRE DE ESPECIE A CARGAR \n");
    fflush(stdin);
    gets(nombre);

    flag = verificaEspecie(arreglo, validos, nombre); //LLAMA A FUNCION QUE DEVUELVE -1 SI NO EXISTE ESPECIE EN ARREGLO

    if (flag == -1)
    {
        printf("LA ESPECIE NO EXISTE, CARGUE DICHA ESPECIE: \n");
        validos = cargaEspecie(arreglo, validos, dim);
        posi = validos - 1;
    }
    else
    {
        posi = flag; //SI EXISTE DICHA ESPECIE DEVUELVE POSICION EN DONDE ESTA DICHA ESPECIE
        lista = arreglo[posi].personajes; //CARGA LISTA CON LISTA DE PERSONAJES EN DICHA ESPECIE
    }

    printf("INGRESE PERSONAJE DE DICHA ESPECIE \n");
    arreglo[posi].personajes = crearListaPersonaje(lista);


    return validos;
}


nodoLista* crearListaPersonaje(nodoLista* lista)
{
    personaje aux;
    nodoLista* nuevoNodo;

    aux = crearPersonaje();
    nuevoNodo = crearNodoPersonaje(aux);


    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoLista* auxLista = lista;
        while (auxLista->siguiente != NULL)
        {
            auxLista = auxLista->siguiente;
        }
        auxLista->siguiente = nuevoNodo;
        nuevoNodo->anterior = auxLista;
    }

    return lista;
}


nodoLista* agregarPpio (nodoLista* lista, nodoLista* nuevoNodo)
{
    if (lista)
    {
        lista->anterior = nuevoNodo;
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        lista = nuevoNodo;
    }

    return lista;

}

void mostrarArregloEspecie(Especie arreglo[], int validos)
{
    int i = 0;
    while(i<validos)
    {
        printf("\n-------------ESPECIE------------\n");
        printf("NOMBRE: %s\n", arreglo[i].nombreEspecie);
        printf("RANGO DE PELIGROSIDAD: %i\n", arreglo[i].rankPeligrosidad);
        mostrarListaPersonajes(arreglo[i].personajes);
        printf("------------------------------------------------\n");
        i++;
    }

}

void mostrarListaPersonajes(nodoLista* lista)
{
    nodoLista* aux = lista;

    printf("-------------LISTA DE PERSONAJES--------------\n");
    while (aux != NULL)
    {
        printf("NOMBRE DE PERSONAJES: %s\n", aux->dato.nombreYapellido);
        printf("EDAD: %i\n", aux->dato.edad);
        printf("DNI: %i\n", aux->dato.dni);
        aux = aux->siguiente;
    }
}


nodoArbol* inicArbol()
{
    return NULL;
}
nodoArbol* pasarListaAArbol(Especie arreglo[], int validos)
{
    int i = 0;
    nodoArbol* nuevoNodo;
    nodoArbol* arbol = inicArbol();
    while (i<validos)
    {
        nuevoNodo = crearNodoArbol(arreglo[i]);
        arbol = insertar (arbol, nuevoNodo);
        i++;

    }

    return arbol;
}

nodoArbol* insertar(nodoArbol* arbol, nodoArbol* nuevoNodo)
{
    if(arbol)
    {
        if(nuevoNodo->dato.rankPeligrosidad < arbol->dato.rankPeligrosidad)
        {
            arbol->izq = insertar(arbol->izq, nuevoNodo);
        }
        else
        {
            arbol->der = insertar(arbol->der, nuevoNodo);

        }

    }
    else
    {
        arbol = nuevoNodo;
    }

    return arbol;
}

nodoArbol* crearNodoArbol(Especie dato)
{
    nodoArbol* aux = (nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato = dato;
    aux->izq = NULL;
    aux->der = NULL;

    return aux;

}

void inOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        inOrder(arbol->izq);
        printf("\n...................................\n");
        printf("NOMBRE DE PERSONAJES: %s\n", arbol->dato.personajes->dato.nombreYapellido);
        printf("EDAD: %i\n", arbol->dato.personajes->dato.edad);
        printf("DNI: %i\n", arbol->dato.personajes->dato.dni);
        printf("\n...................................\n");
        inOrder(arbol->der);
    }
}

void pasarArregloAArchivo(char archivo[], Especie arreglo[], int validos)
{
    int i = 0;
    registroArchivo datos;
    FILE* archi = fopen(archivo, "a+b");
    if(archi)
    {
        while (i<validos)
        {
            strcpy(datos.nombreEspecie,arreglo[i].personajes->dato.nombreYapellido);
            datos.rankPeligrosidad = arreglo[i].rankPeligrosidad;
            while(arreglo[i].personajes!=NULL)
            {
                datos.dni = arreglo[i].personajes->dato.dni;
                datos.edad = arreglo[i].personajes->dato.edad;
                strcpy(datos.nombreYapellido,arreglo[i].personajes->dato.nombreYapellido);

                fwrite(&datos, sizeof(registroArchivo),1,archi);

                arreglo[i].personajes=arreglo[i].personajes->siguiente;
            }
            i++;
        }
    }
}


