#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Función para intercambiar dos nodos en el montículo.
void intercambiar(NodoHeap* a, NodoHeap* b) {
    NodoHeap temp = *a;
    *a = *b;
    *b = temp;
}

// Función para asegurar que el montículo se mantenga como un max-heap.
void max_heapify(Heap* heap, int indice) {
    int max = indice;
    int izquierda = 2 * indice + 1;
    int derecha = 2 * indice + 2;

    if (izquierda < heap->tamano && heap->datos[izquierda].prioridad > heap->datos[max].prioridad) {
        max = izquierda;
    }

    if (derecha < heap->tamano && heap->datos[derecha].prioridad > heap->datos[max].prioridad) {
        max = derecha;
    }

    if (max != indice) {
        intercambiar(&heap->datos[indice], &heap->datos[max]);
        max_heapify(heap, max);
    }
}

// Función para insertar un nuevo elemento en el montículo.
void heap_insertar(Heap* heap, double prioridad, void* data) {
    if (heap->tamano >= heap->capacidad) {
        // Redimension
        heap->capacidad = (heap->capacidad == 0) ? 1 : heap->capacidad * 2;
        heap->datos = (NodoHeap*)realloc(heap->datos, heap->capacidad * sizeof(NodoHeap));
        if (heap->datos == NULL) {
            return;
        }
    }

    int indice = heap->tamano;
    heap->datos[indice].prioridad = prioridad;
    heap->datos[indice].data = data;
    heap->tamano++;

    while (indice > 0 && heap->datos[indice].prioridad > heap->datos[(indice - 1) / 2].prioridad) {
        intercambiar(&heap->datos[indice], &heap->datos[(indice - 1) / 2]);
        indice = (indice - 1) / 2;
    }
}

// Función para extraer el elemento con la mayor prioridad (raíz del montículo).
NodoHeap extraer_max(Heap* heap) {
    if (heap->tamano <= 0) {
        // Monticulo vacio
        NodoHeap nodo_vacio = {0.0, NULL};
        return nodo_vacio;
    }

    NodoHeap max = heap->datos[0];
    heap->tamano--;

    if (heap->tamano > 0) {
        heap->datos[0] = heap->datos[heap->tamano];
        max_heapify(heap, 0);
    }

    return max;
}

// Función para inicializar un montículo con capacidad inicial de 0.
Heap* heap_inicializar() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL) {
        return NULL;
    }
    heap->datos = NULL;
    heap->tamano = 0;
    heap->capacidad = 0;
    return heap;
}

// Función para liberar la memoria utilizada por el montículo.
void liberar_heap(Heap* heap) {
    if (heap) {
        free(heap->datos);
        free(heap);
    }
}
