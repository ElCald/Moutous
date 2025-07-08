#!/bin/bash

export DISPLAY=:0
export XDG_RUNTIME_DIR="/tmp/runtime-$USER"

# Supprimer le répertoire build s'il existe
if [ -d build ]; then
    echo "Suppression du dossier build..."
    rm -rf build
fi

# Créer le dossier build
mkdir build
cd build

# Lancer CMake
echo "Génération du projet avec CMake..."
cmake ..

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

