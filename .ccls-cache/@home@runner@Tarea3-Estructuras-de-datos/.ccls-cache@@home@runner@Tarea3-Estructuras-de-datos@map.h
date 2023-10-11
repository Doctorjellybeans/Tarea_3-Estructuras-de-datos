#ifndef MAP_h
#define MAP_h

#include "libros.h"
#include "list.h"

#define MAX_LEN 100

typedef struct TablaHash {
  int capac;
  int elem;
  Lista* libros[MAX_LEN];
} HashMap;

int hash(int id, int capacidad);

HashMap* createMap(int capacidad);

void destroyMap(HashMap* tabla);

void insertMap(HashMap * tabla, Libro * libro);

void eraseMap(HashMap * tabla, int key);

NodoLista* searchMap(HashMap * tabla, int key);

NodoLista* firstMap(HashMap *tabla);

NodoLista* nextMap(NodoLista *nodo);

#endif