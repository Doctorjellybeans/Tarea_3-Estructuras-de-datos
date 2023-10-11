#ifndef HEAP_h
#define HEAP_h

#define MAX_LEN 100
#include "libros.h"
#include "list.h"

typedef struct heapElem{
  Libro* libro;
  int prioridad;
} heapElem;

typedef struct Heap {
  int size;
  int capac;
  heapElem* heapArray;
} Heap;

Heap* createHeap();

NodoLista* heap_top(Heap* pq);

void heap_push(Heap* pq, Libro* libro, int priority);

void heap_pop(Heap* pq);

#endif
