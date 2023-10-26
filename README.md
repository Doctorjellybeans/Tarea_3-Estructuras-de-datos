# Tarea_#3 Estructuras de datos

# Instrucciones de ejecucion:
1.- ejecutar en el replt(lugar donde se programo)
    link replt: https://replit.com/join/hhbqfszdoc-doctorjellybean
2.-ejecutar con el boton run
#Bugs del codigo:
*La mayoria de errores del programa se asocian a como este gestiona la informacion de cada archivo. El programa no es capaz de hacer un seguimiento al numero de acurrencias de una palabra, debido a esto la mayoria de funciones que requieran de esta variable fallan. En cuanto a su explicación, creemos que este tiene que ver con la clave que se le asigna a cada cadena a la hora de ingresar la cadena en la tabla temporal ya que gracias a esta es que determinamos si la palabra fue previamente ingresada

*Otro de los errores de nuestro programa tiene que ver con la busqueda de libros por titulo. Supongamos que queremos buscar "El principito", si ingresamos ambas palabras no se encontrara el libro PERO si se ingresan palabras adicionales SI se encuentra. Una posible razon es que no estemos procesando de manera correcta la ultima cadena de la entreda por teclado (quizas nos falta eliminar un caracter especial).

*Al momento de calcular la relevancia y la frecuencia, a pesar de que las operaciones se realicen bien la información que se muestra por pantalla es erronea, esto se debe a lo que planteamos al comienzo (la información no se esta guardando correctamente).

Si llamamos a la funcion mostrarContexto esta solo nos mostrara el contexto de la primera ocurrencia de la palabra ingresada por teclado. Esto puede deberse a lo que se plantea en un inicio o a que no se desapile bien la pila de posiciones.
# Contrubuciones individuales:
Vicente Rosales: diseño implementacion de las funciones restantes
nivel contribucion=3;

Alex Alfaro: funcion cargarLibrosDesdeCarpeta,Solucion de diversos Bugs relevantes,ayuda en la creacion de funciones menos relevantes
nivel contribucion=2;
