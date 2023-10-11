#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

int parent(int i){
  return (i-1)/2;
}

Heap* createHeap(){
  Heap* newHeap = (Heap*)malloc(sizeof(Heap));
  
  newHeap->heapArray = (heapElem*)malloc(sizeof(heapElem) * 3);
  newHeap->capac = 3;
  newHeap->size = 0;

  return newHeap;
}

Libro* heap_top(Heap* pq){
  if (pq == NULL){
    printf("Error: heap esta vacio\n");
    return NULL;
  }

  return pq->heapArray[0].libro;
}

void heap_push(Heap* pq, Libro* libro, int priority){
  if (pq == NULL){
    printf("Error: heap esta vacio\n");
    return;
  }

  // Agrandar heap
  if (pq->size == pq->capac){
    pq->heapArray = (heapElem*)realloc(pq->heapArray, sizeof(heapElem) * (pq->capac * 2));
    pq->capac = pq->capac * 2;
  }

  // Proceso de insercion
  int i = pq->size;
  pq->heapArray[i].libro = libro;
  pq->heapArray[i].prioridad = priority;
  
  while (i != 0 && pq->heapArray[parent(i)].prioridad < pq->heapArray[i].prioridad){
    heapElem temp = pq->heapArray[i];
    pq->heapArray[i] = pq->heapArray[parent(i)];
    pq->heapArray[parent(i)] = temp;
    i = parent(i);
  }
  
  pq->size++;
}

void heap_pop(Heap* pq){
  if (pq == NULL){
    printf("Error: heap esta vacio\n");
    return;
  }

  // Proceso de eliminacion
  pq->heapArray[0] = pq->heapArray[pq->size - 1];
  pq->size--;
  int i = 0;
  while (i < pq->size){
    int hijoIzq = 2 * i + 1;
    int hijoDer = 2 * i + 2;
    int hijoMayor = i;

    // Comparacion de prioridades
    if (hijoIzq < pq->size && pq->heapArray[hijoIzq].prioridad > pq->heapArray[hijoMayor].prioridad){
      hijoMayor = hijoIzq;
    }
    
    if (hijoDer < pq->size && pq->heapArray[hijoDer].prioridad > pq->heapArray[hijoMayor].prioridad){
      hijoMayor = hijoDer;
    }

    // Intercambio de prioridades
    if (hijoMayor != i){
      heapElem temp = pq->heapArray[i];
      pq->heapArray[i] = pq->heapArray[hijoMayor];
      pq->heapArray[hijoMayor] = temp;
      i = hijoMayor;
    } else { 
      break; // Terminar proceso
    }
  }
  
}