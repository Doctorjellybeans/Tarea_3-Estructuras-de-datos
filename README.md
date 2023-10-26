# Tarea_#3 Estructuras de datos

# Instrucciones de ejecucion


## Buscador de documentos

La pagina del proyecto Gutenberg ofrece miles de libros gratuitos de manera legal.

- Descargue 100 libros y almacenelos en esta carpeta GDrive 
- El nombre del archivo corresponde a un numero identificador del libro
- El titulo del libro se puede encontrar en la primera linea de cada archivo

  Formato de los libros:
    The project Gutenberg eBook of <nombre del libro>
    ... (contenido del libro)
  
## Las funciones de la aplicaion de terminal deben ser

1) Cargar documentos:
    El usuario *inserta* el nombre del archivo que se desea leer (separados por espacios) y el programa lo lee.
    
2) Mostrar documentos ordenados:
    La aplicacion muestra las id y los titulos de los libros *ORDENADOS* por titulo y ademas se muestra la cantidad de palabras y caracteres que tiene cada libro.
   
3) Buscar un libro por titulo:
    El usuario coloca algunas palabras separadas por espacio y la aplicaion muestra los titulos de libros que contienen todas las palabras.
    
4) Palabras con mayor frecuencia:
    El usuario ingresa el id del libro y la aplicaion muestra las 10 palabras que se repiten con mayor frecuencia (indicando la cantidad de ocurrencias de las mismas).

      Frecuencia = numero_de_ocurrencias / total_de_palabras
    
5) Palabras mas relevantes:
    El usuario ingresa una titulo y la aplicacion muestra la 10 palabras mas relevantes de este.

      p: Relevancia de una palabra
      d: Documento

      Formula: (cant_de_p_en_d / cant_de_palabras_en_d) * log( cant_de_d / cant_de_d_que_contienen_p )
      
6) Buscar por palabra:
    El usuario ingresa una palabra y la aplicaion muestra los libros (id y titulo) que tienen la palabra en su contenido *los libros deben ser ordenados segun la relevancia de la palabra buscada*.

      Ejemplo: si busco jesus, la biblia deberia aparecer primero
    
7) Mostrar palabra en su contexto dentro del libro:
    El usuario ingresa titulo del libro y la palabra que se desea buscar. La aplicaion debe de mostrar las distintas apariciones de la palabra en el documento *con su contexto* (se deben mostrar 5 palabras atras y 5 adelante).

# Metodologia a emplear

## Estrategias:

TDAs: 
  - Mapas
  - Listas
  - Colas de prioridad
  - Pilas
  - \\\\\\

Estructuras:
  - Tablas hash
  - Arreglos
  - Listas enlazadas
  - Monticulos binarios
  - \\\\\\
  
Algoritmos:
  - de ordenacion
  - de busqueda
  - \\\\\\

## Estructura de los nodos (only diseño)

Libro:
  - ID
  - Titulo
  - Texto (palabras del texto)
  - \\\\\\

Texto:
  - Palabra
  - Numero de palabras
  - Numero de caracteres
  - Palabras frecuentes
  - Palabras relevantes
  - \\\\\\

Palabra:
  - Posicion(es)
  - Numero de ocurrencias
  - Palabra
  - \\\\\\

## Sugerencias

1) No es necesario almacenar los textos completos, en la aplicacion *PERO SI LAS PALABRAS*.
2) Use mapas para guardar las palabras de cada libro. Asocie cada palabra al numero de apariciones en el libro.
3) Use mapas o listas oara guardar los titulos asiciados a cada palabra.
4) Para encontrar el contexto de las ocurrencias en cada palabra del documento puede asociar a cada palabra una lista con las posiciones dentro del archivo en donde fue encontrada. Puede usar <ftell> para saber la posicion de las palabras.