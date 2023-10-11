#!/bin/bash

# Compilar el programa
gcc -o my_program main.c

# Verificar si la compilación tuvo éxito
if [ $? -eq 0 ]; then
    # Ejecutar el programa compilado
    ./my_program
else
    echo "Error de compilación."
fi
