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

int parent(int i);

Heap* createHeap();

Libro* heap_top(Heap* pq);

void heap_push(Heap* pq, Libro* libro, int prioridad);

void heap_pop(Heap* pq);

#endif
