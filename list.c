#include "list.h"
#include <stdlib.h>

Lista *lista_inicializar() {
  Lista *nueva_lista = (Lista *)malloc(sizeof(Lista));
  if (nueva_lista != NULL) {
    nueva_lista->cabeza = NULL;
    nueva_lista->cola = NULL;
    nueva_lista->tamano = 0;
  }
  return nueva_lista;
}

#include "list.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// Función para insertar un nuevo nodo en la lista
void lista_insertar(Lista *lista, void *clave, void *dato, size_t tamDato,
                    TipoDato tipo) {
  NodoLista *nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista));
  if (nuevoNodo == NULL) {
    printf("Error al insertar\n");
    return;
  }

  nuevoNodo->clave = clave;
  nuevoNodo->datos = dato;
  nuevoNodo->tamDatos = tamDato;
  nuevoNodo->tipo = tipo;
  nuevoNodo->siguiente = NULL;

  if (tipo == LIBRO) {
    nuevoNodo->pila = pila_inicializar();
  } else {
    nuevoNodo->pila = pila_inicializar(); 
  }

  if (lista->cola == NULL) {
    lista->cabeza = nuevoNodo;
    lista->cola = nuevoNodo;
  } else {
    lista->cola->siguiente = nuevoNodo;
    lista->cola = nuevoNodo;
  }

  lista->tamano++;
}

// Función para buscar un elemento en la lista por clave y tipo
NodoLista *lista_buscar(Lista *lista, void *clave, TipoDato tipo) {
  NodoLista *actual = lista->cabeza;
  while (actual != NULL) {
    if (strcmp(clave, actual->clave) == 0) {
      return actual;
    }
    actual = actual->siguiente;
  }
  return NULL;
}

// Función para liberar la memoria de la lista y sus nodos
void lista_liberar(Lista *lista) {
  NodoLista *actual = lista->cabeza;
  while (actual != NULL) {
    NodoLista *siguiente = actual->siguiente;

    if (actual->tipo == LIBRO) {
      pila_liberar(actual->pila);
      libro_liberar(actual->datos); 
    }

    free(actual);
    actual = siguiente;
  }
  free(lista);
}

// Función para mostrar elementos de la lista
void lista_mostrar(Lista *lista, int num_elementos, ...) {
  if (lista == NULL) {
    printf("lista nula.\n");
    return;
  }

  NodoLista *actual = lista->cabeza;
  while (actual != NULL) {
    printf("-----------------------------\n");
    printf("Clave: %s \n", (char *)actual->clave);

    va_list argumentos;
    va_start(argumentos, num_elementos);

    // Imprimir los elementos de la lista en funcion del tipo
    for (int j = 0; j < num_elementos; j++) {
      TipoDato tipo = va_arg(argumentos, TipoDato);

      if (actual->tipo == LIBRO) {
        printf("-----------------------------\n");
        Libro *libro = (Libro *)actual->datos;
        printf("  - Titulo: %s", libro->titulo);
        printf("  - ID: %s\n", libro->id);
        printf("  - Cantidad de palabras: %d\n",
               libro->texto->cant_total_palabras);
        printf("  - Cantidad de caracteres: %d\n",libro->texto->cant_caracteres);
        printf("-----------------------------\n");
        break;

      } else if (tipo == CADENA) {
        char *cadena = (char *)actual->datos;
        printf("  - Cadena: %s\n", cadena);
        break;
      }
    }
    va_end(argumentos);

    actual = actual->siguiente;
  }
}


// Insertion sort lol
void insertion_sort(Lista* lista) {
  if (lista == NULL || lista->cabeza == NULL) {
    return;
  }

  NodoLista* sorted = NULL;
  NodoLista* actual = lista->cabeza;

  while (actual != NULL) {
    NodoLista* siguiente = actual->siguiente;

    if (sorted == NULL || strcmp((char*)actual->clave, (char*)sorted->clave) <= 0) {
      actual->siguiente = sorted;
      sorted = actual;
    } else {
      NodoLista* temp = sorted;
      while (temp->siguiente != NULL && strcmp((char*)actual->clave, (char*)temp->siguiente->clave) > 0) {
        temp = temp->siguiente;
      }
      actual->siguiente = temp->siguiente;
      temp->siguiente = actual;
    }
    actual = siguiente;
  }
  lista->cabeza = sorted;
}

