#ifndef LIBROS_h
#define LIBROS_h


#include "pila.h"
#define MAX_BUFFER 1024
#define MAX_LEN 100
#define MAX_STR_LEN 80
#include "heap.h"

// Estructura de una palabra en texto del libro
typedef struct {
  char *palabra;        // Puntero a la palabra del documento
  Pila* posiciones;     // Pila de posiciones de la palabra
  int cant_ocurrencias; // Contador de ocurrencias de la palabra
} Palabra;

// Estructura del texto en Libro
typedef struct {
  Palabra *palabras;         // Arreglo de palabras desprendidas del texto
  int cant_total_palabras;   // Contador de palabras en el documento
  int cant_caracteres;       // Contador de caracteres en el documento
  Heap *palabras_frecuentes; // Heap de palabras mas frecuentes den documento
  Heap *palabras_relevantes; // Heap de palabras mas relevantes del documento :(
} Texto;

// Estructura del Libro
typedef struct {
  char *id;     // ID del libro
  char *titulo; // Titulo del libro
  Texto *texto; // Diccionario de palabras del libro
} Libro;

// Funcion que inicializa objeto libro
Libro *libro_inicializar(int cantidadPalabras, int cantCaracteres);

// Funcion para liberar la memoria usada por el objeto libro
void libro_liberar(Libro* libro);

#endif