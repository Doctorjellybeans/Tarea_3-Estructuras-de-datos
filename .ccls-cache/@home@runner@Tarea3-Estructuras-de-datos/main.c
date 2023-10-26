#include "functions.h"
#include <stdio.h>

int main(void) {

  HashMap *mapa = mapa_inicializar(100);
  int opcion, num_documentos;

  do {
    printf(" ======== Menú de opciones ========\n");
    printf("1. Cargar libros desde carpeta\n");
    printf("2. Mostrar documentos ordenados\n");
    printf("3. Buscar libro por título(s)\n");
    printf("4. Mostrar palabras de mayor frecuencia\n");
    printf("5. Mostrar palabras relevantes\n");
    printf("6. Buscar por palabras\n");
    printf("7. Mostrar contexto\n");
    printf("8. Mostrar contenido de la tabla temporal\n");
    printf("9. Salir\n");
    printf("Ingrese el número de la opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      num_documentos = cargarLibrosDesdeCarpeta(mapa);
      break;
    case 2:
      mostrarDocumentosOrdenados(mapa);
      break;
    case 3:
      buscarLibroPorTitulo(mapa);
      break;
    case 4:
      palabrasMayorFrecuencia(mapa);
      break;
    case 5:
      mostrarPalabrasRelevantes(mapa, num_documentos);
      break;
    case 6:
      // buscarPorPalabras();
      break;
    case 7:
      mostrarContexto(mapa);
      break;
    case 8:
      // mostrar_contenido_tabla(mapa);
      break;
    case 9:
      printf("Saliendo del programa.\n");
      break;
    default:
      printf("Opción no válida. Intente de nuevo.\n");
    }
  } while (opcion != 9);

  // freeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
  mapa_liberar(mapa);

  printf("FIN\n"); // en caso de observar este mensaje en la consola, saltar de alegria
  return 0;
}