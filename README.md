# SITAPI - Sistema Integrado de Tutorización de Alumnos de Primer Ingreso

**SITAPI** es una herramienta de gestión académica desarrollada para la Universidad de Córdoba (UCO). Su objetivo es facilitar el seguimiento, la asignación automática de tutores basada en carga de trabajo y compatibilidad, y la comunicación directa mediante chat entre coordinadores, tutores y estudiantes.

## Requisitos Previos (Ubuntu/Linux)

Para compilar y ejecutar este proyecto en un entorno Linux (Ubuntu, Debian, Mint, etc.), es necesario instalar las librerías de desarrollo de Qt6 y SQLite3, además del compilador y CMake.

Ejecuta el siguiente comando en tu terminal para instalar todas las dependencias:

```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev libqt6sql6-sqlite libsqlite3-dev git
```

## Configuracion base de datos

El sistema utiliza SQLite y genera automáticamente su archivo de base de datos (sitapi.db) la primera vez que se ejecuta

**¿Cómo cargar datos personalizados?**

1. Localizar la plantilla: En la carpeta /data del proyecto encontrarás un archivo llamado inserciones.sql con datos ficticios de ejemplo que se añadirán al iniciar el programa

2. En este archivo "inserciones.sql" puedes sobreescribir el código sql con los datos que te interesen **OJO recomendado solo añadir Usuarios, insertar en otras tablas puede resultar en un comportamiento indefinido**

## Compilación y Ejecución

Sigue estos pasos dentro de la carpeta del proyecto para compliar el código fuente:
```bash
mkdir build
cd build
cmake ..
make
./SITAPI
```
Con esto el programa se iniciará, un ejecutable se habrá creado listo para abrir con doble click.

## Autores

Antonio Serrano Maldonado

Adrián Sánchez Prieto

Manuel Téllez Domínguez
