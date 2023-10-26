#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

// Función para inicializar una pila vacía
Pila *pila_inicializar() {
  Pila *pila = (Pila *)malloc(sizeof(Pila));
  if (pila == NULL) {
    return NULL;
  }
  pila->tamano = 0;
  pila->top = NULL;
  pila->bottom = NULL;
  return pila;
}

// Función para verificar si la pila está vacía
int pila_estaVacia(Pila *pila) { return pila->top == NULL; }

// Función para insertar un elemento en la parte superior de la pila (push)
void pila_push(Pila *pila, int data) {
  NodoPila *nuevoNodo = (NodoPila *)malloc(sizeof(NodoPila));
  if (nuevoNodo == NULL) {
    return;
  }
  nuevoNodo->data = data;
  nuevoNodo->next = pila->top;
  pila->top = nuevoNodo;
  if (pila->bottom == NULL) {
    pila->bottom =
        nuevoNodo; 
  }
  pila->tamano++;
}

// Función para eliminar y obtener el elemento en la parte superior de la pila
// (pop)
int pila_pop(Pila *pila) {
  if (pila_estaVacia(pila)) {
    return -1; 
  }
  NodoPila *nodoPop = pila->top;
  int data = nodoPop->data;
  pila->top = nodoPop->next;
  free(nodoPop);
  if (pila->top == NULL) {
    pila->bottom = NULL; 
  }
  pila->tamano--;
  return data;
}

// Función para obtener el elemento en la parte superior de la pila sin
// eliminarlo
int pila_top(Pila *pila) {
  if (pila_estaVacia(pila)) {
    return -1; 
  }
  return pila->top->data;
}

// Función para liberar la memoria de la pila y sus nodos
void pila_liberar(Pila *pila) {
  while (!pila_estaVacia(pila)) {
    pila_pop(pila);
  }
  free(pila);
}

// Función para mostrar los elementos de la pila 
void pila_mostrar(Pila *pila) {
  NodoPila *actual = pila->top;
  while (actual != NULL) {
    printf("%d ", actual->data);
    actual = actual->next;
  }
  printf("\n");
}
