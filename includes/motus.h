#ifndef MOTUS_H
#define MOTUS_H

#include "librairies.h"

#define LISTE_MOTS "misc/mots/liste_mots_simple_FR.txt"

#define CAPACITY 64

using namespace std;

using BS = bitset<CAPACITY>;

enum PLACEMENT{KO, OK, WELL};

int count_num_words_in_list(const string nomFichier);

string getWord(const int pos, const string nomFichier);

string randomWord(const string nomFichier);

vector<int> compareWords(const string input, const string mot, const array<int, 26> alphabet, set<char>& banned_letters);

#endif