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

# ------------------------------------------------------------------------------
# 8. CONFIGURACIÓN DE TESTS (Google Test)
# ------------------------------------------------------------------------------
# Buscamos si GTest está instalado
find_package(GTest)

if(GTest_FOUND)
    message(STATUS "Google Test encontrado. Configurando pruebas...")
    enable_testing()

    # 1. Recopilamos los archivos de lógica (src) OTRA VEZ
    # Importante: Lo hacemos de nuevo para NO incluir "main.cc"
    file(GLOB_RECURSE SRC_PARA_TESTS 
        "src/*.cc" 
        "src/*.cpp"
    )

    # 2. Creamos el ejecutable "run_tests"
    # Junta tu archivo de tests + toda la lógica de tu programa
    add_executable(run_tests 
        tests/unit_tests.cc
        ${SRC_PARA_TESTS}
    )

    # 3. Le damos acceso a las librerías necesarias
    target_link_libraries(run_tests PRIVATE
        GTest::gtest
        GTest::gtest_main
        SQLite::SQLite3
        Qt6::Sql
        Qt6::Widgets
    )
    
    # 4. Aseguramos que pueda encontrar los .h de tu carpeta src
    target_include_directories(run_tests PRIVATE 
        ${CMAKE_SOURCE_DIR}
    )

    # 5. Registramos el test (para poder usar ctest si quieres)
    add_test(NAME UnitTests COMMAND run_tests)

else()
    message(WARNING "Google Test NO encontrado. Saltando configuración de pruebas. (Ejecuta: sudo apt install libgtest-dev)")
endif()