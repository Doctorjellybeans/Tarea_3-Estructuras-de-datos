#ifndef MAP_h
#define MAP_h

#include "list.h"
#include "libros.h"
#include <stdlib.h>
#include <stdint.h>

// Estructura de la lista almacenada en el mapa hash
typedef struct HashEntry {
  struct Lista *lista; 
} HashEntry;

// Estructura del mapa hash
typedef struct HashMap {
  int capacidad;                  // capacidad virtual del mapa
  int tamano;                     // tamaño real del mapa
  struct HashEntry **entradas;    // arreglo de listas
} HashMap;

// Funcion para inicializar mapa hash
HashMap *mapa_inicializar(unsigned int capacidad);

// Funcion para buscar un objeto apartrir de una clave
NodoLista *mapa_buscar(HashMap *mapa, void *clave);

// Funcion para insertar un objeto en un mapa hash
void mapa_insertar(HashMap *mapa, void *clave, void *datos, size_t tamDatos, TipoDato tipo);

// Funcion para liberar memoria usada por el mapa hash
void mapa_liberar(HashMap *mapa);

// Funcion hash
uint32_t fnv1a_hash(const char* str);

// Funcion para mostar el contenido del mapa 
void mostrar_contenido_mapa(HashMap *mapa, int num_elementos, ...);

// Funcion para agrandar el mapa
void mapa_enlarge(HashMap *mapa);

// Funcion para encriptar cadenas (por el momento no uses esta funcion)
char *bytesToHex(const uint8_t *bytes, size_t length);

#endif