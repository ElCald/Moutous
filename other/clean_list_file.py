import unicodedata

def supprimer_accents(texte):
    # Normalisation Unicode + suppression des marques diacritiques
    texte_nfd = unicodedata.normalize('NFD', texte)
    return ''.join(c for c in texte_nfd if unicodedata.category(c) != 'Mn')

def traiter_fichier(entree, sortie):
    mots_uniques = set()

    with open(entree, 'r', encoding='utf-8') as fin:
        for ligne in fin:
            mot = ligne.strip()
            if '-' in mot:
                continue  # Ignore les mots avec un tiret
            mot_sans_accents = supprimer_accents(mot).lower()  # En minuscule (modifie si besoin)
            if mot_sans_accents:
                mots_uniques.add(mot_sans_accents)

    with open(sortie, 'w', encoding='utf-8') as fout:
        for mot in sorted(mots_uniques):  # Trie par ordre alphabétique
            fout.write(mot + '\n')


# Exemple d'utilisation :
traiter_fichier('../misc/mots/liste_mots_FR_raw.txt', '../misc/mots/liste_mots_FR.txt')
