cmake_minimum_required(VERSION 3.16)

# Nombre del proyecto y lenguaje
project(SITAPI LANGUAGES CXX)

# ------------------------------------------------------------------------------
# 1. CONFIGURACIÓN DEL ESTÁNDAR C++ (C++23)
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Forzar estándar puro ISO C++

# Generar compile_commands.json para que VSCode/Clion entiendan el código
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# 2. CONFIGURACIÓN DE QT6 Y AUTOMATIZACIÓN
# ------------------------------------------------------------------------------
set(CMAKE_AUTOMOC ON) # Generar Meta-Object Code (para signals/slots)
set(CMAKE_AUTOUIC ON) # Compilar archivos .ui (si los hubiera)
set(CMAKE_AUTORCC ON) # Compilar recursos .qrc

# Buscar paquetes de Qt requeridos
find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)

# Buscar SQLite3 (Requerido para la base de datos)
find_package(SQLite3 REQUIRED)

# ------------------------------------------------------------------------------
# 3. GESTIÓN DE RUTAS E INCLUDES
# ------------------------------------------------------------------------------
# Esto permite hacer #include "clase.h" directamente sin poner rutas relativas largas
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/models
    ${CMAKE_SOURCE_DIR}/src/repositories
    ${CMAKE_SOURCE_DIR}/src/services
    ${CMAKE_SOURCE_DIR}/src/views
)

# ------------------------------------------------------------------------------
# 4. RECOLECCIÓN DE ARCHIVOS FUENTE
# ------------------------------------------------------------------------------
# Buscamos recursivamente todos los .cc, .cpp y .h dentro de src/
file(GLOB_RECURSE SOURCES 
    "src/*.cc" 
    "src/*.cpp"
)

file(GLOB_RECURSE HEADERS 
    "src/*.h" 
    "src/*.hpp"
)

# Añadimos el main.cc que está en la raíz
list(APPEND SOURCES "main.cc")

# ------------------------------------------------------------------------------
# 5. CREACIÓN DEL EJECUTABLE
# ------------------------------------------------------------------------------
add_executable(SITAPI
    main.cc
    ${SOURCES}
    ${HEADERS}
)

# ------------------------------------------------------------------------------
# 6. ENLAZADO DE LIBRERÍAS (LINKING)
# ------------------------------------------------------------------------------
target_link_libraries(SITAPI PRIVATE
    Qt6::Widgets
    Qt6::Sql
    SQLite::SQLite3
)

# ------------------------------------------------------------------------------
# 7. OPCIONES DE COMPILACIÓN (SEGURIDAD Y CALIDAD)
# ------------------------------------------------------------------------------
# Activar warnings útiles para detectar bugs en Linux (GCC/Clang)
if(UNIX)
    target_compile_options(SITAPI PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Mensaje de éxito al configurar
message(STATUS "Configuración de SITAPI completada. Listo para compilar.")