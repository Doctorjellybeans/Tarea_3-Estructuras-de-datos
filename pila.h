#ifndef PILA_H
#define PILA_H


#include <stdio.h>

// Nodo de la pila
typedef struct NodoPila {
    int data;           // Datos del nodo
    struct NodoPila* next;  // Puntero al siguiente nodo
} NodoPila;

// Definición de la estructura de la pila
typedef struct Pila {
  int tamano;
  struct NodoPila* top;   // Puntero al nodo superior (tope) de la pila
  struct NodoPila* bottom; // Puntero al nodo raiz de la pila
} Pila;

// Función para inicializar una pila vacía
Pila* pila_inicializar();

// Función para verificar si la pila está vacía
int pila_estaVacia(Pila* pila);

// Función para insertar un elemento en la parte superior de la pila (push)
void pila_push(Pila* pila, int data);

// Función para eliminar y obtener el elemento en la parte superior de la pila
// (pop)
int pila_pop(Pila* pila);

// Función para obtener el elemento en la parte superior de la pila sin
// eliminarlo
int pila_top(Pila* pila);

// Funcion para liberar la memoria utilizada por la pila
void pila_liberar(Pila* pila);

// Funcion para mostrar el contenido de la pila
void pila_mostrar(Pila* pila);

#endif