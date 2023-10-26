#ifndef LIST_h
#define LIST_h

#include "libros.h"
#include "pila.h"
#include "string.h"
#include <stddef.h>

// Enumeración para representar los tipos de datos almacenados en la lista
typedef enum {
  CADENA,
  LIBRO,
} TipoDato;

// Estructura del nodo almacenado en la lista
typedef struct NodoLista {
  void *clave;     // Clave del dato
  void *datos;     // Valores recolectados
  size_t tamDatos; // Tamaño de los datos
  TipoDato tipo;   // Tipo de datos (enumeración)
  struct NodoLista *siguiente;
  Pila* pila;
} NodoLista;

// Estructura de la lista
typedef struct Lista {
  NodoLista *cabeza; // Primer elemento de la lista
  NodoLista *cola;   // Último elemento de la lista
  int tamano;        // Tamaño de la lista
} Lista;


// Funcion para inicializar la lista
Lista* lista_inicializar();

// Funcion para insertar objetos con clave en la lista
void lista_insertar(Lista* lista, void* clave, void* dato, size_t tamDato, TipoDato tipo);

// Funcion para encontrar objetos con clave en la lista
NodoLista* lista_buscar(Lista* lista, void* clave, TipoDato tipo);

// Funcion para liberar la memoria usada por lista
void lista_liberar(Lista* lista);

// Funcion para mostrar elementos de la lista
void lista_mostrar(Lista* lista, int num_elementos, ...);

// Insertion sort (ordenar documentos por titulo)
void insertion_sort(Lista* lista);

#endif