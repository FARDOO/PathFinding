cmake_minimum_required(VERSION 3.22)
project(AyED_TPG_1c2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

add_compile_options(-Wall -Werror -Wconversion)

include_directories(include)
include_directories(include/a_estrella)
include_directories(include/aem)
include_directories(include/objetos_mapa)
include_directories(include/minijuego)

# Si crean otros archivos .cpp, los tienen que agregar acá de la forma:
#   directorio/archivo.cpp
set(ARCHIVOS_FUENTE
        include/diccionario.hpp
        include/heap.hpp
        include/nodo.hpp
        include/matriz.hpp
        src/a_estrella/vertice.cpp
        src/a_estrella/a_estrella.cpp
        src/a_estrella/coordenada.cpp
        src/mapa.cpp
        src/aem/grafo.cpp
        src/aem/arista.cpp
        src/objetos_mapa/locales.cpp
        src/objetos_mapa/pedidos.cpp
        src/controlador_juego.cpp
        src/interfaz_de_usuario.cpp
        src/minijuego/minijuego.cpp
)

add_executable(AyED_TPG_1c2024
        ${ARCHIVOS_FUENTE}
        main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e4fdb87e76b9fc4b01c54ad81aea19d6e994b994
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_subdirectory(tests/diccionario)
add_subdirectory(tests/heap)
add_subdirectory(tests/grafo)

target_sources(diccionario_test PRIVATE ${ARCHIVOS_FUENTE})
target_sources(heap_test PRIVATE ${ARCHIVOS_FUENTE})
target_sources(grafo_test PRIVATE ${ARCHIVOS_FUENTE})