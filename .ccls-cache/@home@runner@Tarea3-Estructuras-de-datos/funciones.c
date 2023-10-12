#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Funcion para almacenar cada Libro en Hashmap
void cargarDocumentos(HashMap* hashmap){
  char nombreCarpeta[100];
  printf("Ingrese el nombre de la carpeta ");
  scanf("%s", nombreCarpeta);
// mira el chat
  
  int hashcap=100;
  HashMap* mapa=createMap(hashcap);

  DIR* carpeta;
  struct dirent* entry;
  carpeta = opendir(nombreCarpeta);
  if (carpeta == NULL){
    printf("No se pudo abrir la carpeta");
    return;
  }
  while((entry = readdir(carpeta)) != NULL){
    
    if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name,"..")!=0){
      
      char ruta_archivo[1024];
      
      snprintf(ruta_archivo, sizeof(ruta_archivo),"%s%s",nombreCarpeta,entry->d_name);
      

      FILE *archivo=fopen(ruta_archivo,"r");
      //se abre cada archivo uno por uno
      if(archivo!=NULL){


      }
      
      
    }
      
  
  
  
  /*
  Alex, como sugerencia te recomiendo plantear un tipo de algoritmo que verifique
  si la palabra del libro ya existe, asi no la agregas 2 veces

  para eso se me ocurria que podias utilizar la tabla hash, ir de a poco agregando las
  palabras a la misma pero cada vez que agregues una palabra tienes que verificar si ya
  la agregaste

  mira en el peor de los casos te tendre mañana lista 2 funciones para que llegues y las
  tires aqui

  es que piensa en lo siguiente
  
  typedef struct{
  char palabra[MAX_LEN];
  int posiciones[MAX_LEN]; -> y la palabra aparte tiene posiciones
  int frecuencia;
  } Palabra; 

  // Texto del libro
  typedef struct
    Palabra* palabra[MAX_LEN]; -> la palabra
    int numPalabras; esto 
  } Texto;

  
  // Libros
  typedef struct {
    int id;
    char autor[MAX_LEN];
    char fecha[MAX_LEN];
    char lenguaje[MAX_LEN];
    Texto* texto; -> texto tiene esto
  } Libro;

  piensa que lo que cargara tu funcion es algo como
  libro: (id) -> indice hash 
    autor:
    fecha:
    lenguaje:
    texto: -> aqui debes plantear alguna manera de asociar palabras a un indice de manera efectiva
      palabra1:
      palabra2:
      palabran:
      ...

  en resumen debes crear una funcion hash (puedes utilizar la que teniamos antes pero nose si sea taaaaan
  efectiva, seguro chatgpt tiene otra mejor xd)
  
  ADEMAS
  al final debes de hacer el free de la tabla de palabras, esa funcion la voy a implementar mañana
  no se te puede olvidar eso o si no cagamos brigido XDD

  dale voy a hacer el ultimo push del dia igual creo q lo hare en el c compiler y despues lo pondre aqui por si las moscas
  vale, guardalo en un bloc de notas por si acaso se te pierde el de C compiler

  cambio y fuera (;)
  */

    
}

void mostrarDocumentos(HashMap* hashmap){
  if (hashmap == NULL){
    printf("No hay documentos cargados en la tabla\n");
    return;
  }

  // Recorrer la tabla y guardar los datos en una lista
  Lista* lista = createList();
  for (int i = 0; i < 99; i++){
    if (hashmap->libros[i] != NULL){
      
      NodoLista* current = hashmap->libros[i]->head;
      while (current != NULL){
        pushFront(lista, current->libro);
        current = current->next;
      }
    }
  }

  // Ordenar lista por titulo
  insertionSort(lista,1);

  // Mostrar lista ordenada por titulo
  printf("Lista de documentos ordenada por titulo:\n");


  // Liberar lista
  cleanList(lista);
  free(lista);
}