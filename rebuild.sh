#!/bin/bash

export DISPLAY=:0
export XDG_RUNTIME_DIR="/tmp/runtime-$USER"

if [ "$1" == "windows" ]; then
    echo "Compilation Windows"
    # Supprimer le répertoire build_release s'il existe
    if [ -d build_release ]; then
        echo "Suppression du dossier build_release..."
        rm -rf build_release
    fi

    # Créer le dossier build_release
    mkdir build_release
    cd build_release

    # Lancer CMake
    echo "Génération du projet avec CMake..."
    cmake -DCMAKE_TOOLCHAIN_FILE=../mingw-toolchain.cmake .. -DTARGET=windows




elif [ "$1" == "linux" ]; then
    echo "Compilation Linux"
    # Supprimer le répertoire build_debug s'il existe
    if [ -d build_debug ]; then
        echo "Suppression du dossier build_debug..."
        rm -rf build_debug
    fi

    # Créer le dossier build_debug
    mkdir build_debug
    cd build_debug

    # Lancer CMake
    echo "Génération du projet avec CMake..."
    cmake .. -DTARGET=linux



else
    echo "Usage : $0 [windows|linux]"
    exit 1
fi


# Vérifier si cmake a réussi
if [ $? -eq 0 ]; then
    echo "Configuration CMake réussie."
else
    echo "Erreur lors de la configuration CMake."
    exit 1
fi

# Compiler le projet
echo "Compilation avec make..."
make -j$(nproc)
if [ $? -eq 0 ]; then
    echo "Build terminé avec succès."
else
    echo "Erreur lors de la compilation."
    exit 1
fi
