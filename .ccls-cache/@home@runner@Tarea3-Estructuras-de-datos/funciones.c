    #include "functions.h"
    #include <ctype.h>
    #include <dirent.h>
    #include <math.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #define MAXBUFFER 1024
    #define tamaño 100

    // ---------------------------------------------------------------------- //

    // Funcion que cuenta cada palabra en el documento
    int ContarPalabras(const char *ruta_archivo) {
      int cont = 0;
      FILE *archivo = fopen(ruta_archivo, "r");
      char linea[1024];
      const char *lineaDeseada = "*** START";
      char delimitadores[] = " ,.:\"()?\n\t";

      if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return -1;
      }

      // Saltar hasta texto
      while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (strstr(linea, lineaDeseada) != NULL) {
          break;
        }
      }

      // Inicio proceso
      while (fgets(linea, sizeof(linea), archivo)) {
        if (strlen(linea) <= 1 && linea[0] == '\n') {
          continue;
        }

        char *token = strtok(linea, delimitadores);
        while (token != NULL) {
          cont++;
          token = strtok(NULL, delimitadores);
        }
      }

      fclose(archivo);
      return cont;
    }

    // Funcion para contar caracteres de un archivo
    int ContarCaracteres(const char *ruta_archivo) {
      int cont = 0;
      FILE *archivo = fopen(ruta_archivo, "r");
      char caracter;

      if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return -1;
      } else {
        while ((caracter = fgetc(archivo)) != EOF) {
          cont++;
        }

        fclose(archivo);
        return cont;
      }
    }

    char *ExtraerTitulo(const char *ruta_archivo) {
      FILE *archivo = fopen(ruta_archivo, "r");
      char linea[MAXBUFFER];
      char delimitadores[] = " ,.:\"()?\n\t";
      if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
      } else {
        const char *lineaDeseada = "Title: ";
        char texto_despues[100]; // Declaración fuera del bucle
        while (fgets(linea, sizeof(linea), archivo) != NULL) {
          if (strstr(linea, lineaDeseada) != NULL) {
            const char *inicio = strstr(linea, lineaDeseada);

            if (inicio != NULL) {
              inicio += strlen(lineaDeseada);
              strcpy(texto_despues, inicio);
            }

            fclose(archivo);
            return strdup(texto_despues); // Devuelve una copia dinámica del texto
          }
        }
      }
      return NULL;
    }

    void eliminarSaltoDeLinea(char *cadena) {
      int longitud = strlen(cadena);

      for (int i = 0; i < longitud; i++) {
        if (cadena[i] == '\n') {
          cadena[i] = '\0';
          break; // Detenemos el bucle una vez que se encuentra el primer salto de
                 // línea
        }
      }
    }

    int contarPalabras(const char *cadena) {
      int palabras = 0;
      bool enPalabra = false;

      while (*cadena) {
        if (*cadena == ' ' || *cadena == '\t' || *cadena == '\n') {
          enPalabra = false;
        } else if (!enPalabra) {
          enPalabra = true;
          palabras++;
        }

        cadena++;
      }

      return palabras;
    }

    // Función que divide una cadena en palabras y las almacena en un arreglo de
    // punteros
    char **dividir_en_palabras(const char *cadena, int *num_palabras) {
      char *copia = strdup(
          cadena); // Hacemos una copia de la cadena para no modificar la original
      char **arreglo = NULL;
      char *palabra = strtok(copia, " ");
      int count = 0;

      while (palabra != NULL) {
        arreglo = realloc(arreglo, (count + 1) * sizeof(char *));
        arreglo[count] = strdup(palabra);
        palabra = strtok(NULL, " ");
        count++;
      }

      *num_palabras = count;
      free(copia);

      return arreglo;
    }

    // Función que elimina las palabras duplicadas de un arreglo de punteros
    void eliminar_palabras_duplicadas(char **arreglo, int *num_palabras) {
      for (int i = 0; i < *num_palabras; i++) {
        for (int j = i + 1; j < *num_palabras; j++) {
          if (arreglo[i] && arreglo[j] && strcmp(arreglo[i], arreglo[j]) == 0) {
            free(arreglo[j]);
            arreglo[j] = NULL;
          }
        }
      }

      int new_count = 0;
      for (int i = 0; i < *num_palabras; i++) {
        if (arreglo[i]) {
          arreglo[new_count] = arreglo[i];
          new_count++;
        }
      }

      *num_palabras = new_count;
      arreglo = realloc(arreglo, new_count * sizeof(char *));
    }

    Libro *buscarLibro(HashMap *mapa, char *titulo) {
      for (int i = 0; i < mapa->capacidad; i++) {
        if (mapa->entradas[i]->lista != NULL) {
          NodoLista *current = mapa->entradas[i]->lista->cabeza;
          while (current != NULL) {
            if (strcmp(((Libro *)current->datos)->titulo, titulo) == 0) {
              return (Libro *)current->datos;
            }
            current = current->siguiente;
          }
        }
      }
      return NULL;
    }

    Pila *buscarPila(Libro *libro, char *palabra) {
      int i = 0;
      while (libro->texto->palabras[i].palabra != NULL) {

        if (strcmp(libro->texto->palabras[i].palabra, palabra) == 0) {
          return libro->texto->palabras[i].posiciones;
        }

        i++;
      }
    }

    void formarContexto(int posicion, Libro *libro) {

      int start, end;

      if (posicion <= 5) {
        end = posicion + 5;
        printf("Contexto: ");
        for (int i = 0; i < end; i++) {
          printf("%s ", libro->texto->palabras[i].palabra);
        }
        printf("\n");
      } else {

        start = posicion - 5;
        end = posicion + 5;
        printf("\n=================== [START] ===================\n");
        printf("Contexto: ");
        for (int i = start; i < end; i++) {
          printf("%s ", libro->texto->palabras[i].palabra);
        }
        printf("\n==================== [END] ====================\n\n");
        ;
      }
    }

    int contarOcurrenciasPorDocumentos(char *palabra, HashMap *mapa, char *titulo) {
      int contador = 0;
      for (int i = 0; i < mapa->capacidad; i++) {
        if (mapa->entradas[i]->lista != NULL) {
          NodoLista *current = mapa->entradas[i]->lista->cabeza;
          while (current != NULL && ((Libro *)current->datos)->titulo != titulo) {
            if (strcmp(((Libro *)current->datos)->texto->palabras[i].palabra,
                       palabra) == 0) {
              contador++;
            }
            current = current->siguiente;
          }
        }
      }
      return contador;
    }
    // ---------------------------------------------------------------------- //

    // Funcion #1
    int cargarLibrosDesdeCarpeta(HashMap *hashmap) {
      char carpeta[100];
      printf("Ingrese el nombre de la carpeta: ");
      scanf("%s", carpeta);

      DIR *dir;
      struct dirent *entry;

      dir = opendir(carpeta);

      if (dir == NULL) {
        perror("error al abrir");
        return -1;
      }

      // Ruta de los archivos
      int numero_documentos = 0;
      while ((entry = readdir(dir)) != NULL) {
        // Ignora las entradas especiales . y ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
          continue;
        }

        // Construye la ruta completa al archivo
        char archivo_path[MAXBUFFER];
        snprintf(archivo_path, sizeof(archivo_path), "%s/%s", carpeta,
                 entry->d_name);

        // Contar y inicializar libro
        int cant_caracteres = ContarCaracteres(archivo_path);
        int cant_palabras = ContarPalabras(archivo_path);
        Libro *libro = libro_inicializar(cant_palabras, cant_caracteres);

        // Extraer ID
        char cadena[20];
        int id = atoi(entry->d_name);
        sprintf(cadena, "%d", id);
        libro->id = cadena;
        printf("Procesando archivo: %s\n", entry->d_name);
        FILE *archivo = fopen(archivo_path, "r");
        char delimitadores[] = " ,.:\"()?\n\t";

        // Extraer titulo
        if (archivo != NULL) {
          char linea[MAXBUFFER];
          char *tokenTitle;
          char *title = ExtraerTitulo(archivo_path);
          eliminarSaltoDeLinea(title);
          libro->titulo = title;

          const char *lineaDeseada = "*** START";
          while (fgets(linea, sizeof(linea), archivo) != NULL) {
            if (strstr(linea, lineaDeseada) != NULL) {
              break;
            }
          }

          // Informacion del proceso
          printf("\n========= [INFO] =========\n");
          printf("ID: %s\n", libro->id);
          printf("Titulo: %s\n", libro->titulo);
          printf("Cantidad de caracteres: %d\n", libro->texto->cant_caracteres);
          printf("Cantidad de palabras: %d\n", libro->texto->cant_total_palabras);
          printf("==========================\n\n");

          // Inicia la lectura de palabras
          HashMap *tabla_temp = mapa_inicializar(cant_palabras);
          int posicion1 = 0; // pos de la 1ra ocurrencia de una palabra
          int posicion2 = 0; // pos de la 2da ocurrencia en adelante de una palabra

          while (fgets(linea, sizeof(linea), archivo) != NULL) {
            char *token = strtok(linea, delimitadores);
            while (token != NULL) {

              int temp = strlen(token);
              char *clave = token;


              if (mapa_buscar(tabla_temp, clave) ==
                  NULL) { // Si la palabra es nueva, agregar a tabla_temp
                          // y a la vez sumar contadores e apilar pos 1

                mapa_insertar(tabla_temp, clave, token, strlen(token) + 1, CADENA);

                libro->texto->palabras[posicion1].palabra = strdup(token);
                libro->texto->palabras[posicion1].cant_ocurrencias++;

                NodoLista *nodo = mapa_buscar(tabla_temp, clave);
                pila_push(nodo->pila, posicion1);
                pila_push(libro->texto->palabras[posicion1].posiciones, posicion1);

                posicion1++;
              } else if (mapa_buscar(tabla_temp, clave) != NULL) {
                NodoLista *nodo = mapa_buscar(tabla_temp, clave);

                pila_push(
                    libro->texto->palabras[nodo->pila->bottom->data].posiciones,
                    posicion2);
                libro->texto->palabras[nodo->pila->bottom->data].cant_ocurrencias++;
              }
              posicion2++;
              token = strtok(NULL, delimitadores);
            }
          }

          /*for (int i = 0; i < posicion2; i++) {
            if (libro->texto->palabras[i].palabra == NULL) continue;
            printf("Palabra: %s | Cantidad: %d\n",
          libro->texto->palabras[i].palabra,
          libro->texto->palabras[i].cant_ocurrencias);

          }*/

          // Liberamos la tabla
          mapa_liberar(tabla_temp);
        }

        // Insertamos el libro en la tabla principal , +1 documento
        mapa_insertar(hashmap, libro->id, libro, sizeof(Libro), LIBRO);
        fclose(archivo);
        numero_documentos++;
      }

      return numero_documentos;
    }

    void mostrarDocumentosOrdenados(HashMap *mapa) {
      if (mapa == NULL)
        return;

      Lista *lista_ordenada = lista_inicializar();

      for (int i = 0; i < mapa->capacidad; i++) {
        if (mapa->entradas[i]->lista != NULL) {
          NodoLista *current = mapa->entradas[i]->lista->cabeza;
          while (current != NULL) {
            Libro *libro = libro_inicializar(
                ((Libro *)current->datos)->texto->cant_total_palabras,
                ((Libro *)current->datos)->texto->cant_caracteres);

            libro->id = ((Libro *)current->datos)->id;
            libro->titulo = ((Libro *)current->datos)->titulo;
            libro->texto->cant_caracteres =
                ((Libro *)current->datos)->texto->cant_caracteres;
            libro->texto->cant_total_palabras =
                ((Libro *)current->datos)->texto->cant_total_palabras;

            lista_insertar(lista_ordenada, libro->titulo, libro, sizeof(Libro),
                           LIBRO);

            current = current->siguiente;
          }
        }
      }

      // Ordenar lista en orden alfabetico
      insertion_sort(lista_ordenada);

      // Mostrar lista "ordenada"
      printf("\n======== [START] ========\n");
      lista_mostrar(lista_ordenada, 1, LIBRO);
      printf("======== [ END ] ========\n\n");

      // liberar lista y libros dentro de lista
      lista_liberar(lista_ordenada);
    }

    void buscarLibroPorTitulo(HashMap *mapa) {
      getchar();
      char palabras[100];
      printf("Ingrese el titulo del libro que desea buscar: ");
      fgets(palabras, sizeof(palabras), stdin);
      eliminarSaltoDeLinea(palabras);

      int num_palabras;
      char **arreglo_entrada = dividir_en_palabras(palabras, &num_palabras);
      eliminar_palabras_duplicadas(arreglo_entrada, &num_palabras);

      // Recorrer hashmap y crear lista de titulos
      Lista *lista_titulos = lista_inicializar();
      for (int i = 0; i < mapa->capacidad; i++) {
        if (mapa->entradas[i]->lista != NULL) {
          NodoLista *current = mapa->entradas[i]->lista->cabeza;
          while (current != NULL) {

            // Obtenemos la informacion
            char *titulo = ((Libro *)current->datos)->titulo;
            char *id = ((Libro *)current->datos)->id;

            // Insertamos en la lista
            lista_insertar(lista_titulos, id, titulo, sizeof(titulo), CADENA);

            current = current->siguiente;
          }
        }
      }

      // Buscamos ocurrencias comunes
      NodoLista *current = lista_titulos->cabeza;
      while (current != NULL) {

        char titulo[150];
        strcpy(titulo, (char *)current->datos);

        int flag = 0; // si flag == num_palabras_titulo, mostramos titulo

        int num_palabras_titulo = contarPalabras((char *)current->datos);
        char *token = strtok((char *)current->datos, " ");

        while (token != NULL) {
          for (int i = 0; i < num_palabras; i++) {
            printf("arreglo[%d]: %s | %lu\n", i, arreglo_entrada[i],
                   strlen(arreglo_entrada[i]));
            printf("Token      : %s | %lu\n\n", token, strlen(token));
            if (strcmp(token, arreglo_entrada[i]) == 0) {

              flag++;

              // Mostramos el titulo
              if (flag == num_palabras_titulo) {
                printf("\n=========== [INFO] ===========\n");
                printf("Titulo: %s \n", titulo);
                printf("------------------------------\n\n");
                break;
              }
            }
          }
          token = strtok(NULL, " ");
        }

        current = current->siguiente;
      }

      // liberar
      lista_liberar(lista_titulos);
    }

    void palabrasMayorFrecuencia(HashMap *mapa) {
      if (mapa == NULL) {
        return;
      }

      getchar();
      char id[100];
      printf("Ingrese ID: ");
      fgets(id, sizeof(id), stdin);
      eliminarSaltoDeLinea(id);

      if (mapa_buscar(mapa, id) == NULL) {
        printf("\n*** No se encontro el libro ***\n");
        return;
      } else {
        NodoLista *nodo = mapa_buscar(mapa, id);
        Libro *libro = (Libro *)nodo->datos;

        int cant_palabras = libro->texto->cant_total_palabras;
        Heap *heap_temp = libro->texto->palabras_frecuentes;

        int i = 0;
        while (libro->texto->palabras[i].palabra != NULL) {
          char *palabra = libro->texto->palabras[i].palabra;
          int cant_de_ocurrencias = libro->texto->palabras[i].cant_ocurrencias;

          double frecuencia = (double)cant_de_ocurrencias / (double)cant_palabras;

          heap_insertar(heap_temp, frecuencia, palabra);

          i++;
        }

        // Imprimir palabras con mayor frecuencia (recorrer heap)
        printf("\n======================== [START] ========================\n");
        for (int i = 0; i < 10; i++) {
          printf("  - Top #%d: %-16s | prioridad: %lf\n", i + 1,
                 (char *)heap_temp->datos[i].data, heap_temp->datos[i].prioridad);
        }
        printf("======================== [ END ] ========================\n\n");

        liberar_heap(heap_temp);
      }
    }

    void mostrarPalabrasRelevantes(HashMap *mapa, int num_documentos) {
      if (mapa == NULL) {
        return;
      }

      getchar();
      char titulo[100];
      printf("Ingrese titulo del libro: ");
      fgets(titulo, sizeof(titulo), stdin);
      eliminarSaltoDeLinea(titulo);

      Libro *libro = buscarLibro(mapa, titulo);

      Heap *heap_relevancia = libro->texto->palabras_relevantes;
      int i = 0;
      while (libro->texto->palabras[i].palabra != NULL) {
        char *palabra = libro->texto->palabras[i].palabra;
        int cant_de_ocurrencias = libro->texto->palabras[i].cant_ocurrencias;

        int p_en_documentos = contarOcurrenciasPorDocumentos(
            palabra, mapa, titulo); // buscar palabra en documentos
        double relevancia = ((double)libro->texto->palabras[i].cant_ocurrencias /
                             (double)libro->texto->cant_total_palabras) *
                            log((double)num_documentos / (double)p_en_documentos);

        printf("============================\n");
        printf("cant_ocurrencias: %d\n", cant_de_ocurrencias);
        printf("num_documentos %d\n", num_documentos);
        printf("cant_total: %d\n", libro->texto->cant_total_palabras);
        printf("p_en_documentos: %d\n", p_en_documentos);
        printf("============================\n");

        heap_insertar(heap_relevancia, relevancia, palabra);
        i++;
      }

      // Imprimir palabras con mayor relevancia (recorrer heap)
      printf("\n======================== [START] ========================\n");
      for (int i = 0; i < 10; i++) {
        printf("  - Top #%d: %-16s | prioridad: %lf\n", i + 1,
               (char *)heap_relevancia->datos[i].data,
               heap_relevancia->datos[i].prioridad);
      }
      printf("======================== [ END ] ========================\n\n");

      liberar_heap(heap_relevancia);
    }

    void mostrarContexto(HashMap *mapa) {
      if (mapa == NULL) {
        return;
      }

      getchar();
      char titulo_entrada[100];
      printf("Ingrese Titulo: ");
      fgets(titulo_entrada, sizeof(titulo_entrada), stdin);
      eliminarSaltoDeLinea(titulo_entrada);

      char palabra[100];
      printf("Ingrese la palabra deseada: ");
      fgets(palabra, sizeof(palabra), stdin);
      eliminarSaltoDeLinea(palabra);

      // buscar libro
      if (buscarLibro(mapa, titulo_entrada) != NULL) {
        Libro *libro = buscarLibro(mapa, titulo_entrada);

        Pila *pila_posiciones = buscarPila(libro, palabra);

        while (pila_posiciones->bottom != NULL) {
          int posicion = pila_pop(pila_posiciones);

          formarContexto(posicion, libro);
        }

      } else {
        printf("** No se encontro el libro **\n\n");
      }

      // Mostrar contexto
    }
