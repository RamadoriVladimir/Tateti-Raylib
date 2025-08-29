#!/bin/bash

RAYLIB_PATH="/usr/local/raylib" 

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' 
echo "--- Verificando y preparando el entorno ---"

if [ ! -d "build" ]; then
    mkdir build
    echo -e "${GREEN}Directorio 'build' creado. 🛠️${NC}"
fi

if [ ! -d "src" ]; then
    echo -e "${RED}Error: No se encontró la carpeta 'src'.${NC}"
    echo "Por favor, crea una y coloca tus archivos .cpp alli."
    exit 1
fi

echo "--- Iniciando compilación de Raylib ---"
CFLAGS="-std=c++14 -Wall -Wextra -O2 -I$RAYLIB_PATH/include -L$RAYLIB_PATH/lib"
LDFLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt"

if [ -f "build/programa" ]; then
    echo "Limpiando ejecutable anterior: build/programa"
    rm build/programa
fi

echo "--- Compilando con G++... ---"
echo "Versión de G++:"
g++ --version
echo "---"

g++ src/*.cpp $CFLAGS $LDFLAGS -o build/programa

if [ $? -ne 0 ]; then
    echo -e "${RED}¡Fallo en la compilación!${NC}"
    exit 1
else
    echo -e "${GREEN}¡Compilación exitosa! Ejecutable en build/programa${NC}"
fi

echo "--- Ejecutando 'programa' ---"
echo "------------------------------"
if [ -f "build/programa" ]; then
    ./build/programa
else
    echo -e "${RED}Error: No se encontró el ejecutable en build/programa.${NC}"
    exit 1
fi

echo "--- Proceso completado ---"