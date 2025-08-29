@echo off
setlocal

set RAYLIB_PATH=C:\raylib\raylib
set COMPILER_PATH=C:\raylib\w64devkit\bin

if not exist build (
    mkdir build
    echo Directorio 'build' creado. 🛠️
)

if not exist src (
    echo.
    echo  Error: No se encontro la carpeta 'src'.
    echo Por favor, crea una y coloca tus archivos .cpp alli.
    goto :end
)

echo.
echo Preparando entorno y compilando 
echo -------------------------------------------------------------

set PATH=%COMPILER_PATH%;%PATH%

set CFLAGS=%RAYLIB_PATH%\src\raylib.rc.data -s -static -O2 -std=c++14 -Wall -I%RAYLIB_PATH%\src -Iinclude -DPLATFORM_DESKTOP
set LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm

if exist build\programa.exe (
    echo.
    echo Limpiando ejecutable anterior: build\programa.exe
    del /F build\programa.exe
)

echo.
echo Iniciando compilacion con G++...
echo Version de G++:
g++ --version
echo.
echo Comando de compilacion:
echo g++ -o build\programa.exe src\*.cpp %CFLAGS% %LDFLAGS%
g++ -o build\programa.exe src\*.cpp %CFLAGS% %LDFLAGS%

if %errorlevel% neq 0 (
    echo.
    echo  ¡Fallo en la compilacion! 
    goto :end
) else (
    echo.
    echo  Compilacion exitosa. Ejecutable en build\programa.exe
    echo.
)

echo Ejecutando 'programa.exe'...
echo ------------------------------
if exist build\programa.exe (
    start build\programa.exe
) else (
    echo Error: No se encontro el ejecutable en build\programa.exe.
)

:end
endlocal

echo.
pause