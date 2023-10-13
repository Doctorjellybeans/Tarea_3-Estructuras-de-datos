#ifndef HEAP_h
#define HEAP_h

#define MAX_LEN 100
#include "libros.h"
#include "map.h"
#include "list.h"

#define MAX_HEAP_SIZE 100

// Estructura del nodo almacenado en el montículo binario
typedef struct NodoMonticulo {
    void* key; // se calcula con strHash
    void* value; // diccionario de palabras del libro
    int priority; // dependiendo del montículo, se equilibra por frecuencia o relevancia
} NodoMonticulo;

// Estructura del montículo binario
typedef struct Monticulo {
    NodoMonticulo heap[MAX_HEAP_SIZE]; // arreglo de diccionarios de palabras
    int size; // tamaño del monticulo
} Monticulo;

Monticulo* createMonticulo();

void initMonticulo(Monticulo* heap);

void insertHeap(Monticulo* heap, const void* key, const void* value, int priority);

NodoMonticulo* extractHeap(Monticulo* heap);

#endif
