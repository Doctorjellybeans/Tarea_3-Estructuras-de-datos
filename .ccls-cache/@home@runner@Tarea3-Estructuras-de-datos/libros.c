#include "libros.h"
#include "heap.h"
#include <stdlib.h>
#include <string.h>

// Función para inicializar un libro con la cantidad especificada de palabras
Libro *libro_inicializar(int cantidadPalabras, int cantidadCaracteres) {
  Libro *libro = (Libro *)malloc(sizeof(Libro));
  if (libro == NULL) {
    // Manejo de error
    return NULL;
  }

  libro->id = NULL;
  libro->titulo = NULL;

  // Inicializa el texto del libro
  libro->texto = (Texto *)malloc(sizeof(Texto));
  if (libro->texto == NULL) {
    free(libro);
    // Manejo de error
    return NULL;
  }

  libro->texto->palabras =
      (Palabra *)malloc(sizeof(Palabra) * cantidadPalabras);
  if (libro->texto->palabras == NULL) {
    free(libro->texto);
    free(libro);
    return NULL;
  }

  libro->texto->cant_total_palabras = cantidadPalabras;
  libro->texto->cant_caracteres = cantidadCaracteres;

  // Inicializa las estructuras de montículo para palabras frecuentes y
  // relevantes
  libro->texto->palabras_frecuentes = heap_inicializar();
  libro->texto->palabras_relevantes = heap_inicializar();

  for (int i = 0; i < cantidadPalabras; i++) {
    libro->texto->palabras[i].cant_ocurrencias = 0;
    libro->texto->palabras[i].posiciones = pila_inicializar();
  }
  return libro;
}

void libro_liberar(Libro *libro) {
  if (libro == NULL) {
    return;
  }

  // Libera la memoria de las palabras en el texto del libro
  if (libro->texto != NULL && libro->texto->palabras != NULL) {
    free(libro->texto->palabras);
  }

  // Libera la memoria de las estructuras de montículo
  if (libro->texto != NULL) {
    liberar_heap(libro->texto->palabras_frecuentes);
    liberar_heap(libro->texto->palabras_relevantes);
  }

  // Libera la memoria del texto del libro y del libro en sí
  if (libro->texto != NULL) {
    free(libro->texto);
  }
  free(libro);
}
