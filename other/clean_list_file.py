import unicodedata

def supprimer_accents(texte):
    texte_nfd = unicodedata.normalize('NFD', texte)
    return ''.join(c for c in texte_nfd if unicodedata.category(c) != 'Mn')

def traiter_fichier(entree, sortie):
    mots_uniques = set()

    with open(entree, 'r', encoding='latin-1') as fin:  # ← Encodage corrigé
        for ligne in fin:
            mot = ligne.strip()
            if '-' in mot or ' ' in mot:
                continue
            mot_sans_accents = supprimer_accents(mot).lower()
            if mot_sans_accents:
                mots_uniques.add(mot_sans_accents)

    with open(sortie, 'w', encoding='utf-8') as fout:
        for mot in sorted(mots_uniques):
            fout.write(mot + '\n')

# Exemple d'utilisation
traiter_fichier('../misc/mots/liste_FREELANG_FR_raw.txt', '../misc/mots/liste_FREELANG_FR.txt')
