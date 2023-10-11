#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

Heap* createHeap(){
  Heap* newHeap = (Heap*)malloc(sizeof(Heap));
  
  newHeap->heapArray = (heapElem*)malloc(sizeof(heapElem) * 3);
  newHeap->capac = 3;
  newHeap->size = 0;

  return newHeap;
}

NodoLista* heap_top(Heap* pq){
  
}

void heap_push(Heap* pq, Libro* libro, int priority){
  
}

void heap_pop(Heap* pq){
  
}