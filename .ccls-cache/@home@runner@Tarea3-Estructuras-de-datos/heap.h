#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo con información y prioridad.
typedef struct {
  double prioridad;
  void *data;
} NodoHeap;

// Estructura para representar un montículo binario.
typedef struct {
  NodoHeap *datos; // Un arreglo para almacenar los nodos del montículo.
  int tamano;      // El número actual de elementos en el montículo.
  int capacidad;   // La capacidad máxima del montículo.
} Heap;

// Función para inicializar un montículo sin capacidad inicial.
Heap *heap_inicializar();

// Función para liberar la memoria utilizada por el montículo.
void liberar_heap(Heap *heap);

// Función para insertar un nuevo elemento en el montículo.
void heap_insertar(Heap *heap, double prioridad, void *data);

// Función para extraer el elemento con la mayor prioridad (raíz del montículo).
NodoHeap extraer_max(Heap *heap);

// Función para asegurar que el montículo se mantenga como un max-heap.
void max_heapify(Heap *heap, int indice);

#endif