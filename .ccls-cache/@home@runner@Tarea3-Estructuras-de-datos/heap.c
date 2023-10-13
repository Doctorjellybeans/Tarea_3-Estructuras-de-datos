#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

Monticulo* createMonticulo() {
    Monticulo* heap = (Monticulo*)malloc(sizeof(Monticulo));
    if (heap == NULL) {
        // Manejar error de asignación de memoria
        exit(EXIT_FAILURE);
    }
    heap->size = 0;
    return heap;
}


void initMonticulo(Monticulo* heap) {
    heap->size = 0;
}

void insertHeap(Monticulo* heap, const void* key, const void* value, int priority) {
    if (heap->size == MAX_HEAP_SIZE) {
        // Montículo lleno, manejar según sea necesario (por ejemplo, aumentar la capacidad).
        return;
    }

    NodoMonticulo* newNode = &(heap->heap[heap->size]);
    newNode->key = (void*)key;
    newNode->value = (void*)value;
    newNode->priority = priority;

    int index = heap->size;
    int parent = (index - 1) / 2;

    while (index > 0 && heap->heap[parent].priority > newNode->priority) {
        // Intercambiar con el padre si es necesario para mantener la propiedad del montículo.
        heap->heap[index] = heap->heap[parent];
        index = parent;
        parent = (index - 1) / 2;
    }

    heap->heap[index] = *newNode;
    heap->size++;
}

NodoMonticulo* extractHeap(Monticulo* heap) {
    if (heap->size == 0) {
        return NULL; // Montículo vacío.
    }

    NodoMonticulo* minNode = &(heap->heap[0]);
    heap->size--;

    // Mover el último nodo al principio y ajustar para mantener la propiedad del montículo.
    heap->heap[0] = heap->heap[heap->size];

    int index = 0;
    int leftChild, rightChild, minChild;

    while (1) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        minChild = index;

        if (leftChild < heap->size && heap->heap[leftChild].priority < heap->heap[minChild].priority) {
            minChild = leftChild;
        }

        if (rightChild < heap->size && heap->heap[rightChild].priority < heap->heap[minChild].priority) {
            minChild = rightChild;
        }

        if (minChild != index) {
            // Intercambiar con el hijo mínimo si es necesario para mantener la propiedad del montículo.
            NodoMonticulo temp = heap->heap[index];
            heap->heap[index] = heap->heap[minChild];
            heap->heap[minChild] = temp;

            index = minChild;
        } else {
            break;
        }
    }

    return minNode;
}