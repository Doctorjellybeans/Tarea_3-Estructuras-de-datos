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

void printLista(Lista* lista){
  if (lista == NULL){
    printf("La lista no existe\n");
    return;
  }

  NodoLista* current = lista->head;

  while (current != NULL){
    
    // Datos principales
    printf("=========[ %s ]=========", current->libro->titulo);
    printf("ID: %d \n", current->libro->id);
    printf("Autor: %s\n", current->libro->autor);
    printf("Fecha: %s\n", current->libro->fecha);
    printf("Lenguaje: %s\n", current->libro->lenguaje);

    // Palabras del texto
    
  }
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
  
  printf("Lista limpiada\n");
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

// 
void insertionSort(Lista* lista, int opcion){
  if (lista == NULL){
    printf("Lista no existente, no se puede ordenar\n");
    return;
  }

  NodoLista* sorted = NULL; // lista ordenada
  NodoLista* current = lista->head; // nodo actual
  
  switch (opcion){
    case 1:
      printf("Ordenar por titulo\n");
      while (current != NULL){
        NodoLista* next = current->next; // Guardamos el siguiente nodo antes de borrar el actual

        if (sorted == NULL || strcmp(sorted->libro->titulo, current->libro->titulo) < 0){
          
          current->next = sorted;
          current->prev = NULL;
          if (sorted != NULL){
            sorted->prev = current;
          }
          sorted = current;

          if (current->next == NULL){
            lista->tail = current;
          }
        } else {
          // Buscamos la posicion correcta en la lista ordenada e insertamos el nodo
          NodoLista* temp = sorted;
          while (temp->next != NULL && strcmp(temp->next->libro->titulo, current->libro->titulo) >= 0){
            temp = temp->next;
          }

          current->next = temp->next;
          if (temp->next != NULL){
            temp->next->prev = current;
          }
          
          current->prev = temp;
          temp->next = current;
          
          if (current->next == NULL){
            lista->tail = current;
          }
        }
        current = next;
      }

      lista->head = sorted;
      break;
    case 2:
      printf("Ordenar por relevancia de palabra\n");
      // Falta implementar funcion de calculo de relevancia
      
      break;
    default:
      printf("Opcion no valida\n");
      
  }

}
  
