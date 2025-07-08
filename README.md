# Moutous

Jeu adapté de l'emission "Motus" et repris des jeux "Tusmo" et "Wordle". <br>

L'objectif est de trouver le mot mystère avec 6 propositions.

### Guide 
- Lettres en vert -> correctes et bien placées
- Lettres en rouge -> correctes et mal placées
- Lettres classiques -> incorrectes

Appuis sur la touche `Enter` pour valider. <br>
Appuis sur la touche `Tab` pour afficher le mot.

------------------------
<img src="/other/exemple/moutous_demo.gif" alt="Exemple en gif du jeu Moutous" width="" height=""/>


## Compilation
### Debug
```
./rebuild.sh linux
```
Génération d'un exécutable pour un environnement Linux dans le répertoire `build_debug`.

### Release
```
./rebuild.sh windows
```
Génération d'un exécutable pour un environnement Windows dans le répertoire `build_release`. Pour compacter l'application, faire un zip du `moutous.exe`, `bin/` et `misc/`.

## Annexe
Liste de mots : [liste](http://www.3zsoftware.com/fr/listes.php)
