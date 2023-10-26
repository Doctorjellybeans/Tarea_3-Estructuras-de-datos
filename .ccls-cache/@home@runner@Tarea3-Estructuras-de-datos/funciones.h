#ifndef FUNCTIONS_h
#define FUNCTIONS_h

#include <stdio.h>
#include "libros.h"
#include "list.h"
#include "map.h"
#include "pila.h"
#include "heap.h"

int cargarLibrosDesdeCarpeta(HashMap* hashmap);

void mostrarDocumentosOrdenados(HashMap* hashmap);

void palabrasMayorFrecuencia();

void buscarLibroPorTitulo(HashMap *mapa);

void mostrarPalabrasRelevantes(HashMap* mapa, int num_documentos);

void buscarPorPalabras();

void mostrarContexto(HashMap* mapa);

void mostrar_contenido_tabla_temp(HashMap *tabla_temp);

#endif