#ifndef LIST_h
#define LIST_h

#define MAX_LEN 100
#include "libros.h"

typedef struct NodoLista{
  Libro* libro;
  NodoLista* next;
  NodoLista* prev;
} NodoLista;

typedef struct Lista {
  NodoLista* head;
  NodoLista* tail;
  int size;
} Lista;

Lista* createList();

void pushFront(Lista * list, Libro* data);

void pushBack(Lista * list, Libro* data);

void pushCurrent(Lista * list, Libro* data);

void popFront(Lista * list);

void popBack(Lista * list);

NodoLista* findData(Lista * list, int id);

void cleanList(Lista * list);

#endif