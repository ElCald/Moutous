import pandas as pd

# Charger le fichier Lexique383
df = pd.read_csv("../misc/mots/Lexique383.tsv", sep="\t", encoding="utf-8")


# -------------------------------
# FILTRAGE DES MOTS
# -------------------------------

# Longueur : mots de 5 à 8 lettres
df = df[(df["nblettres"] >= 5) & (df["nblettres"] <= 8)]

# Fréquence : mots pas trop rares (fréquence > 1 dans les sous-titres de films)
df = df[df["freqfilms2"] > 1]

# Catégories grammaticales : noms, verbes conjugués, adjectifs
df = df[df["cgram"].isin(["NOM", "VER", "ADJ"])]

# Exclusion de mots indésirables : majuscules, apostrophes, tirets...
df = df[~df["ortho"].str.contains(r"[A-Z\-'\s]", regex=True)]

# Suppression des doublons
mots_uniques = df["ortho"].drop_duplicates().sort_values()

# -------------------------------
# SAUVEGARDE DANS UN FICHIER TXT
# -------------------------------

with open("../misc/mots/liste_moutous.txt", "w", encoding="utf-8") as f:
    for mot in mots_uniques:
        f.write(mot + "\n")

print(f"{len(mots_uniques)} mots enregistrés")
