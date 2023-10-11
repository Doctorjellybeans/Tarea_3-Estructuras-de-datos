#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "map.h"

int hash(int id, int capacidad){
  return id % capacidad;
}

HashMap* createMap(int capacidad){
  HashMap* tabla = (HashMap*)malloc(sizeof(HashMap));
  if (tabla == NULL){
    printf("Error al asignar memoria para la tabla\n");
    return NULL;
  }
  tabla->capac = capacidad;
  tabla->elem = 0;

  for (int i = 0; i < capacidad; i++){
    tabla->libros[i] = NULL;
  }

  return tabla;
}

void insertMap(HashMap * tabla, Libro * libro) {
    int indice = hash(libro->id, tabla->capac);

    // Creamos el nodo
    NodoLista *nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria para el nodo\n");
        return;
    }

    // Asignamos los valores
    nuevoNodo->libro = libro;
    nuevoNodo->next = NULL;
    nuevoNodo->prev = NULL;

    // Verificamos si existen colisiones
    if (tabla->libros[indice] == NULL) {
        // Si no hay colisión, creamos la nueva lista
        Lista *nuevaLista = createList();

        pushFront(nuevaLista, libro);

        tabla->libros[indice] = nuevaLista;
        tabla->elem++;
    } else {
        // Si hay colision, agregamos el nodo a la lista
        pushFront(tabla->libros[indice], libro);
        tabla->elem++;
    }
}

NodoLista* firstMap(HashMap *tabla){
  if (tabla->libros[0] == NULL){
    return NULL;
  }
  
  return tabla->libros[0]->head;
}

NodoLista* nextMap(NodoLista *nodo){
  if (nodo == NULL || nodo->next){
    return NULL;
  }
  
  return nodo->next;
}

NodoLista* searchMap(HashMap * tabla, int id) {
    if (tabla == NULL) {
        printf("Error al buscar el libro\n");
        return NULL;
    }

    int indice = hash(id, tabla->capac);

    if (tabla->libros[indice] == NULL) {
        // No hay lista en este índice, por lo que el libro no está en la tabla
        printf("No se encontró el libro en la tabla\n");
        return NULL;
    }

    // Utilizamos findData para buscar el libro en la lista
    return findData(tabla->libros[indice], id);
}


void destroyMap(HashMap* tabla) {
    for (int i = 0; i < tabla->capac; i++) {
        if (tabla->libros[i] != NULL) {
            cleanList(tabla->libros[i]);
            free(tabla->libros[i]);
        }
    }
    free(tabla);
}
