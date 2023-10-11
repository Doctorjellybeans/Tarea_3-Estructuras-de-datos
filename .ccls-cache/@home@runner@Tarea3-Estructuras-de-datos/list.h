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

void pushFront(Lista * lista, Libro* data);

void pushBack(Lista * lista, Libro* data);

void pushCurrent(Lista * lista, Libro* data);

void popFront(Lista * lista);

void popBack(Lista * lista);

NodoLista* findData(Lista * lista, int id);

void cleanList(Lista * lista);

void insertionSort(Lista* lista);

#endif