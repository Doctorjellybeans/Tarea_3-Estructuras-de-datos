#ifndef FUNCIONES_h
#define FUNCIONES_h

#include "libros.h"
#include "list.h"
#include "heap.h"
#include "map.h"

#define MAX_LEN 100

void cargarDocumentos(HashMap* hashmap);

void mostrarDocumentos(HashMap* hashmap);

void Mayor_frecuencia();

void mostrarPalabrasRelevantes();

void buscarPorPalabras();

void mostrarContexto();


#endif