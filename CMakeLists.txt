cmake_minimum_required(VERSION 3.15)

project(Trabajo2_GL LANGUAGES CXX)

# Usa C++17 para tu proyecto
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar las librerías necesarias con vcpkg
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Añadir todos los archivos fuente
set(SOURCES
    Main.cpp
    Entorno.cpp
    Jugador.cpp
    rubik.cpp
)

# Crear el ejecutable
add_executable(Trabajo2 ${SOURCES})

# Enlazar con GLEW y OpenGL
target_link_libraries(Trabajo2 PRIVATE GLEW::GLEW OpenGL::GL)

# Para evitar warnings con MSVC (Visual Studio)
if(MSVC)
  target_compile_options(Trabajo2 PRIVATE /W4 /permissive-)
else()
  target_compile_options(Trabajo2 PRIVATE -Wall -Wextra -pedantic)
endif()
