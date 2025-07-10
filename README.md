# Moutous

Jeu adapté de l'émission "Motus" et repris des jeux "Tusmo" et "Wordle". <br>

L'objectif est de trouver le mot mystère avec 6 propositions. Le jeu se compose d'une liste d'environ 12 000 mots provenant de [Lexique383](http://www.lexique.org), une base de données bien plus importante permet d'essayer une multitude de mots de la langue française lors des propositions.

### Guide 
- Lettres en vert -> correctes et bien placées
- Lettres en rouge -> correctes et mal placées
- Lettres classiques -> incorrectes

Appuis sur la touche `Enter` pour valider. <br>
Appuis sur la touche `Space` pour changer de mot. <br>
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
Génération d'un exécutable pour un environnement Windows dans le répertoire `build_release` avec une archive zip. 

## Annexe
Un script python `clean_list_file.py` permet de retirer les accents, éviter la casse et retirer les mots avec des tirets ou des espaces. <br><br>

Liste de mots : 
- [liste 1](http://www.3zsoftware.com/fr/listes.php)
- [liste 2](http://www.lexique.org)


