#include "map.h"

// Función para inicializar el mapa hash
HashMap *mapa_inicializar(unsigned int capacidad) {
  HashMap *mapa = (HashMap *)malloc(sizeof(HashMap));
  if (mapa == NULL) {
    // Manejo de error
    return NULL;
  }
  mapa->capacidad = capacidad;
  mapa->tamano = 0;

  // Asigna memoria para el arreglo de entradas
  mapa->entradas = (HashEntry **)malloc(sizeof(HashEntry *) * capacidad);
  if (mapa->entradas == NULL) {
    // Manejo de error
    free(mapa);
    return NULL;
  }

  // Inicializa las entradas del mapa
  for (int i = 0; i < capacidad; i++) {
    mapa->entradas[i] = (HashEntry *)malloc(sizeof(HashEntry));
    mapa->entradas[i]->lista = lista_inicializar();
  }

  return mapa;
}

// Función para buscar un elemento en el mapa hash por clave
NodoLista *mapa_buscar(HashMap *mapa, void *clave) {

  // Calcula el índice utilizando la función de hash
  uint32_t indice = fnv1a_hash(clave) % mapa->capacidad;
  //if (strcmp(clave, "90") == 0) printf("La encontro en mapa!\n");
  return lista_buscar(mapa->entradas[indice]->lista, clave, CADENA);
}

// Función de hash FNV-1a para cadenas
uint32_t fnv1a_hash(const char *str) {
  uint32_t hash = 2166136261u; // Valor inicial recomendado
  while (*str) {
    hash ^= (uint32_t)*str++;
    hash *= 16777619u; // Primo grande
  }
  return hash;
}

// Función para insertar un elemento en el mapa hash
void mapa_insertar(HashMap *mapa, void *clave, void *datos, size_t tamDatos,
                   TipoDato tipo) {
  // Calcular indice
  uint32_t indice = fnv1a_hash(clave) % mapa->capacidad;

  if (mapa->tamano >= mapa->capacidad * 0.75) {
    mapa_enlarge(mapa);
    // Rehash
    indice = fnv1a_hash(clave) % mapa->capacidad;
  }

  // Insertar en la lista correspondiente al índice
  lista_insertar(mapa->entradas[indice]->lista, clave, datos, tamDatos, tipo);
  mapa->tamano++;
}

// Función para liberar la memoria del mapa hash
void mapa_liberar(HashMap *mapa) {
  for (int i = 0; i < mapa->capacidad; i++) {
    lista_liberar(mapa->entradas[i]->lista);
    free(mapa->entradas[i]);
  }
  free(mapa->entradas); // Liberar el arreglo de entradas
  free(mapa);
}

// Función para mostrar el contenido del mapa hash
void mostrar_contenido_mapa(HashMap *mapa, int num_elementos, ...) {
  if (mapa == NULL) {
    printf("Mapa nulo.\n");
    return;
  }

  printf("-----------[START]-----------\n");

  for (int i = 0; i < mapa->capacidad; i++) {
    Lista *lista_actual = mapa->entradas[i]->lista;

    if (lista_actual != NULL) {
      NodoLista *actual = lista_actual->cabeza;

      while (actual != NULL) {
        printf("Clave: %s | Hash: %d\n", (char *)actual->clave,i);

        va_list argumentos;
        va_start(argumentos, num_elementos);

        for (int j = 0; j < num_elementos; j++) {
          TipoDato tipo = va_arg(argumentos, TipoDato);

          if (actual->tipo == LIBRO) {
            Libro *libro = (Libro *)actual->datos;
            printf("  - ID: %s     | len %ld\n", libro->id, strlen(libro->id));
            printf("  - Titulo: %s | len %ld\n", libro->titulo, strlen(libro->titulo));
            int i = 0;
            while (libro->texto->palabras[i].palabra != NULL){         
              char* palabra = libro->texto->palabras[i].palabra;
              int cant = libro->texto->palabras[i].cant_ocurrencias;
              printf("    - Palabra: %s #%d |",palabra,i);
              printf(" cantida: %d \n",cant);
              i++;
            }
            break;
          } else if (actual->tipo == CADENA) {
            char *cadena = (char *)actual->datos;
            printf("  - Cadena: %s\n", cadena);
            break;
          }
        }
        va_end(argumentos);

        printf("-----------------------------\n");
        actual = actual->siguiente;
      }
    }
  }
}

void mapa_enlarge(HashMap *mapa) {
  // Calcula el nuevo tamaño del mapa (duplica la capacidad actual)
  int nueva_capacidad = mapa->capacidad * 2;

  // Crea un nuevo mapa con la nueva capacidad
  HashMap *nuevo_mapa = mapa_inicializar(nueva_capacidad);

  // Reinserta todos los elementos del mapa actual en el nuevo mapa
  for (int i = 0; i < mapa->capacidad; i++) {
    Lista *lista_actual = mapa->entradas[i]->lista;
    NodoLista *actual = lista_actual->cabeza;

    while (actual != NULL) {
      mapa_insertar(nuevo_mapa, actual->clave, actual->datos, actual->tamDatos, actual->tipo);
      actual = actual->siguiente;
    }
  }

  // Libera la memoria del mapa anterior
  mapa_liberar(mapa);

  // Asigna el nuevo mapa al mapa original
  *mapa = *nuevo_mapa;
  free(nuevo_mapa);
}

char *bytesToHex(const uint8_t *bytes, size_t length) {
    char *hexStr = malloc(2 * length + 1);
    if (hexStr) {
        for (size_t i = 0; i < length; i++) {
            sprintf(&hexStr[i * 2], "%02x", bytes[i]);
        }
        hexStr[2 * length] = '\0';
    }
    return hexStr;
}