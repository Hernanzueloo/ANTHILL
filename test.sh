#!/bin/bash

# Comprobar si se han pasado todos los argumentos esperados
if [ $# -lt 1 ]; then
    echo "Uso: $0 [0|1] nombre_fichero_pruebas_sin_extension"
    exit 1
fi

# Obtener el primer argumento
modo=$1

# Obtener el segundo argumento o establecer un valor por defecto
if [ $# -lt 2 ]; then
    fichero=$(cd src && ls *_test.c 2>/dev/null | sed 's/\.c//g')
else
    fichero=$2
fi

# Compilar el fichero indicado utilizando make
make $fichero

# Ejecutar el programa de prueba según el modo indicado
if [[ $modo -eq 0 ]]; then
    if [ $# -lt 2 ]; then
        for ejecutable in $fichero
        do
            ./bin/$ejecutable
        done
    else
        ./bin/$fichero
    fi
elif [[ $modo -eq 1 ]]; then
    if [ $# -lt 2 ]; then
        for ejecutable in $fichero
        do
            valgrind --leak-check=full ./bin/$ejecutable
        done
    else
        valgrind --leak-check=full ./bin/$fichero
    fi
else
    echo "Uso: $0 [0|1] nombre_fichero_pruebas_sin_extension"
    exit 1
fi