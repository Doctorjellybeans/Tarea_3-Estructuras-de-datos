#ifndef LIST_h
#define LIST_h

#define MAX_LEN 100
#include "libros.h"
#include "heap.h"

// Estructura del nodo almacenado en la lista
typedef struct NodoLista {
    void* key; // se calcula con intHash
    void* value; // contiene id, titulo, autor, fecha y lenguaje del libro
    struct NodoLista* next;
    struct NodoLista* prev;
    struct Monticulo* heapFrecuancia;
    struct Monticulo* heapRelevancia;
} NodoLista;

// Estructura de la lista 
typedef struct Lista {
    struct NodoLista* head; // primer elemento de la lista
    struct NodoLista* tail; // ultimo elemento de la lista
    int size; // tamaño de la lista
} Lista;

Lista* createLista();

void initLista(Lista* lista);

void pushBack(Lista* lista, const void* key, const void* value);

NodoLista* findNode(Lista* lista, const void* key);

#endif