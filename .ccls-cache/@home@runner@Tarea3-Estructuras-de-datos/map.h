#ifndef MAP_h
#define MAP_h

#include "libros.h"
#include "list.h"

#define MAX_LEN 100

// Estructura de la lista almacenada en la tabla hash
typedef struct HashEntry {
    struct Lista* lista; // puntero al primer nodo de la lista
} HashEntry;

// Estructura de la tabla hash
typedef struct HashMap {
    int capac; // capacidad del mapa
    int size; // tamaño del mapa
    struct HashEntry* entradas[MAX_LEN]; // arreglo de listas
    unsigned int (*funcionHash)(const void* key); // funcion hash
} HashMap;

unsigned int hashParaInt(const void* key);

unsigned int hashParaString(const void* key);

HashMap* createHashMap(int capac, unsigned int (*funcionHash)(const void* key));

void insert(HashMap* map, const void* key, const void* value);

void* get(HashMap* map, const void* key);

NodoLista* getFirstElement(HashMap* map);

#endif