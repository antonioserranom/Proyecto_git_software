# SITAPI - Sistema Integrado de Tutorización de Alumnos de Primer Ingreso

**SITAPI** es una herramienta de gestión académica desarrollada para la Universidad de Córdoba (UCO). Su objetivo es facilitar el seguimiento, la asignación automática de tutores basada en carga de trabajo y compatibilidad, y la comunicación directa mediante chat entre coordinadores, tutores y estudiantes.

## 📋 Requisitos Previos (Ubuntu/Linux)

Para compilar y ejecutar este proyecto en un entorno Linux (Ubuntu, Debian, Mint, etc.), es necesario instalar las librerías de desarrollo de Qt6 y SQLite3, además del compilador y CMake.

Ejecuta el siguiente comando en tu terminal para instalar todas las dependencias:

```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev libqt6sql6-sqlite libsqlite3-dev git
