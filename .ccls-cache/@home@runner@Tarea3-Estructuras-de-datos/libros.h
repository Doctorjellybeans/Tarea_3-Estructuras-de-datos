#ifndef LIBROS_h
#define LIBROS_h
#define MAX_LEN 100

// Palabra en el Texto del Libro
typedef struct{
  char palabra[MAX_LEN];
  int posiciones[MAX_LEN];
  int frecuencia;
} Palabra;

// Texto del libro
typedef struct{
  Palabra* palabra[MAX_LEN];
  int numPalabras;
} Texto;


// Libros
typedef struct {
  int id;
  char titulo[MAX_LEN];
  Texto* texto;
} Libro;


#endif