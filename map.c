#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "map.h"

#define TABLE_SIZE 100

// Función de hash para enteros
unsigned int hashParaInt(const void* key) {
    return *((const int*)key) % TABLE_SIZE;
}

// Función de hash para cadenas de texto (string)
unsigned int hashParaString(const void* key) {
    const char* str = (const char*)key;
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % MAX_LEN;
}

HashMap* createHashMap(int capac, unsigned int (*funcionHash)(const void* key)) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->capac = capac;
    map->size = 0;
    map->funcionHash = funcionHash;

    for (int i = 0; i < capac; ++i) {
        map->entradas[i] = (HashEntry*)malloc(sizeof(HashEntry));
        map->entradas[i]->lista = (Lista*)malloc(sizeof(Lista));
        initLista(map->entradas[i]->lista);
    }

    return map;
}

void insert(HashMap* map, const void* key, const void* value) {
    unsigned int hash = map->funcionHash(key);
    HashEntry* entry = map->entradas[hash];
    pushBack(entry->lista, key, value);
    map->size++;
}

void* get(HashMap* map, const void* key) {
    unsigned int hash = map->funcionHash(key);
    HashEntry* entry = map->entradas[hash];
    NodoLista* node = findNode(entry->lista, key);

    if (node != NULL) {
        return node->value;
    } else {
        return NULL;
    }
}

NodoLista* getFirstElement(HashMap* map) {
    for (int i = 0; i < map->capac; ++i) {
        if (map->entradas[i]->lista->head != NULL) {
            return map->entradas[i]->lista->head;
        }
    }
    return NULL;  // Si la tabla está vacía
}
