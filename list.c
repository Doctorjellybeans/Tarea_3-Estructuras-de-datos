#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "list.h"

Lista* createList(){
  Lista* lista = (Lista*)malloc(sizeof(Lista));
  lista->head = NULL;
  lista->tail = NULL;
  lista->size = 0;
  return lista;
}

// insertar al frente de la lista
void pushFront(Lista * lista, Libro* libro){
  if (lista == NULL){
    printf("Lista no existente, no se puede insertar por delante\n");
    return;
  }

  // creamos el nodo
  NodoLista* nodo = (NodoLista*)malloc(sizeof(NodoLista));
  nodo->libro = libro;
  nodo->next = NULL;
  nodo->prev = NULL;

  if (lista->head == NULL){
    lista->head = nodo;
    lista->tail = nodo;
  
  } else {
    nodo->next = lista->head;
    lista->head->prev = nodo;
    lista->head = nodo;
  }
  lista->size++;
}

// insertar al final de la lista
void pushBack(Lista * lista, Libro* libro){
  if (lista == NULL){
    printf("Lista no existente, no se puede insertar por atras\n");
    return;
  }
  
  // creamos el nodo
  NodoLista* nodo = (NodoLista*)malloc(sizeof(NodoLista));
  nodo->libro = libro;
  nodo->next = NULL;
  nodo->prev = NULL;
  
  if (lista->head == NULL){
    lista->head = nodo;
    lista->tail = nodo;
  } else {
    nodo->prev = lista->tail;
    lista->tail->next = nodo;
    lista->tail = nodo;
  }
  lista->size++;
}

void popFront(Lista * lista){
  if (lista == NULL){
    printf("Lista no existente, no se puede eliminar por delante\n");
    return;
  }
  
  if (lista->head == NULL){
    printf("Lista vacia, no se puede eliminar\n");
    return;
  }
  
  NodoLista* nodo = lista->head;
  lista->head = nodo->next;
  if (lista->head == NULL){
    lista->tail = NULL;
  } else {
    lista->head->prev = NULL;
  }
  free(nodo);
  lista->size--;
}

void popBack(Lista * lista){
  if (lista == NULL){
    printf("Lista no existente, no se puede eliminar por atras\n");
    return;
  }
  
  if (lista->head == NULL){
    printf("Lista vacia, no se puede eliminar\n");
    return;
  }
  
  NodoLista* nodo = lista->tail;
  lista->tail = nodo->prev;
  if (lista->tail == NULL){
    lista->head = NULL;
  } else {
    lista->tail->next = NULL;
  }
  
  free(nodo);
  lista->size--;
}

void cleanList(Lista * lista){
  if (lista == NULL){
    printf("Lista no existente, no se puede limpiar\n");
    return;
  }
  
  while (lista->head != NULL){
    popFront(lista);
  }
  
  lista->tail = NULL;
  lista->size = 0;
}

NodoLista* findData(Lista * list, int id){
  if (list == NULL){
    printf("Lista no existente, no se puede buscar\n");
    return NULL;
  }

  NodoLista* nodo = list->head;
  while (nodo != NULL){
    if (nodo->libro->id == id){
      return nodo;
    }
    nodo = nodo->next;
  }

  printf("No se encontro el Libro\n");
  return NULL;
}
  
