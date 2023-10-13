#include "funciones.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBUFFER 1024

char *ExtraerTitulo(FILE *archivo) {
  char linea[MAXBUFFER];
  if (fgets(linea, sizeof(linea), archivo) != NULL) {
    if (strncmp(linea, "Title: ", 7) == 0) {
      char *titulo = malloc(strlen(linea) - 7);

      if (titulo != NULL) {
        strncpy(titulo, linea + 7, strlen(linea) - 7);
        return titulo;
      }
    } else {
      printf("no se encontro");
    }
  } else {
    printf("no hay nada");
  }
  return NULL;
}

void mostrarDocumentos(HashMap *tabla) {
  if (tabla == NULL) {
    printf("No se ingreso correctamente la tabla para mostrar documentos");
    return;
  }

  // recorrer la tabla y insertar elementos en una lista
  Lista *lista = createLista();
  for (int i = 0; i < tabla->size; i++) {
    pushBack(lista, const void *key, const void *value)
  }
}

// Funcion para almacenar cada Libro en Hashmap
void cargarDocumentos(HashMap *hashmap) {
  char linea[MAXBUFFER];
  char nombreCarpeta[100];
  printf("Ingrese el nombre de la carpeta: ");
  scanf("%s", nombreCarpeta);

  DIR *carpeta;
  struct dirent *entry;
  carpeta = opendir(nombreCarpeta);
  if (carpeta == NULL) {
    printf("No se pudo abrir la carpeta.\n");
    return;
  }

  while ((entry = readdir(carpeta)) != NULL) {

    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

      char ruta_archivo[MAXBUFFER];
      snprintf(ruta_archivo, sizeof(ruta_archivo), "%s/%s", nombreCarpeta,
               entry->d_name);

      int id = atoi(entry->d_name);
      int indice = hashParaInt(&id);
      Libro *libro = (Libro *)malloc(sizeof(Libro));

      libro->id = id;

      FILE *archivo = fopen(ruta_archivo, "r");
      if (archivo != NULL) {

        char delimitadores[] = " ,.:\"()\n\t";
        HashMap *temp_tabla = createHashMap(250, hashParaString);
        Texto *texto = (Texto *)malloc(sizeof(Texto));

        // Saltar las primeras 10 líneas
        for (int i = 0; i < 10; i++) {
          fgets(linea, sizeof(linea), archivo);
        }

        char *title = ExtraerTitulo(archivo);
        strcpy(libro->titulo, title);
        free(title);

        // Saltar intro del libro
        for (int i = 0; i < 10; i++) {
          fgets(linea, sizeof(linea), archivo);
        }

        // Separar palabra por palabra
        while (fgets(linea, sizeof(linea), archivo)) {
          char *token = strtok(linea, delimitadores);
          while (token != NULL) {
            Palabra *palabra = (Palabra *)malloc(sizeof(Palabra));

            // Verificar si la palabra ya está en la tabla temporal
            if (get(temp_tabla, token) == NULL) {
              texto->numPalabras++;
              palabra->contPalabra++;
              strcpy(palabra->palabra, token);
              // ftell para las posiciones
              // la frecuencia se calcula después
              // la relevancia se calcula después
              insert(temp_tabla, palabra->palabra, palabra);
            } else {
              texto->numPalabras++;
              free(palabra);
            }

            token = strtok(NULL, delimitadores);
          }
        }

        /*
        Monticulo *monticuloRelevancia = crearMonticuloPorTabla(temp_tabla);
        Monticulo *monticuloFrecuencia = crearMonticuloPorTabla(temp_tabla);
        */
        
        //liberarTabla(temp_tabla);
        fclose(archivo);
      }

      free(libro);
    }
  }

  closedir(carpeta);
}