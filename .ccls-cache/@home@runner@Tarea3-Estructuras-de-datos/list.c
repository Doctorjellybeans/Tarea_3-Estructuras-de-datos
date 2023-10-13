#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "list.h"

Lista* createLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        // Manejar error de asignación de memoria
        exit(EXIT_FAILURE);
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
    return lista;
}

void initLista(Lista* lista) {
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
}

void pushBack(Lista* lista, const void* key, const void* value) {
    NodoLista* newNode = (NodoLista*)malloc(sizeof(NodoLista));
    newNode->key = (void*)key;
    newNode->value = (void*)value;
    newNode->next = NULL;

    newNode->heapFrecuencia = (Monticulo*)malloc(sizeof(Monticulo));
    initMonticulo(newNode->heapFrecuencia);

    newNode->heapRelevancia = (Monticulo*)malloc(sizeof(Monticulo));
    initMonticulo(newNode->heapRelevancia);

    if (lista->tail == NULL) {
        newNode->prev = NULL;
        lista->head = newNode;
        lista->tail = newNode;
    } else {
        newNode->prev = lista->tail;
        lista->tail->next = newNode;
        lista->tail = newNode;
    }

    lista->size++;
}

NodoLista* findNode(Lista* lista, const void* key) {
    NodoLista* current = lista->head;
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
  
