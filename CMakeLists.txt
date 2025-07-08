cmake_minimum_required(VERSION 3.14)
project(Moutous)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Windows-specific settings ---
set(WINDOWS_LIBS
    -lsetupapi
    -lwinmm
    -limm32
    -lversion
    -ldinput8
    -ldxguid
    -ldxerr8
    -luser32
    -lgdi32
    -lwinmm
    -limm32
    -lole32
    -loleaut32
    -lshell32
    -lsetupapi
    -lversion
    -luuid
    -static-libgcc
    -static-libstdc++
)

# Indiquer les chemins vers SDL2
set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/SDL_lib/SDL2/include")
set(SDL2_LIB_DIR "${CMAKE_SOURCE_DIR}/SDL_lib/SDL2/lib")

# Inclure les dossiers d'includes
include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    includes
)

# Récupérer les sources
file(GLOB_RECURSE SOURCES src/*.cpp)

# Créer l'exécutable
add_executable(main WIN32 ${SOURCES})

# Linker les libs SDL2 (attention à l'ordre)
target_link_libraries(main
    
    -lmingw32
    "${SDL2_LIB_DIR}/libSDL2.a"
    "${SDL2_LIB_DIR}/libSDL2main.a"
    "${SDL2_LIB_DIR}/libSDL2_ttf.a"
    "${WINDOWS_LIBS}"
    -lrpcrt4            # pour les gui Windows
    -mwindows           # pour les gui Windows
)

# Copier les DLLs dans le dossier de build pour l'exécutable
file(COPY SDL_lib/SDL2/bin DESTINATION ${CMAKE_BINARY_DIR})


# Copier dossier misc (si tu en as besoin)
file(COPY misc DESTINATION ${CMAKE_BINARY_DIR})

