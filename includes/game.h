#ifndef GAME_H
#define GAME_H

#include "librairies.h"
#include "utiles.h"


#define MOTS_CLASSIQUE "misc/mots/petit_larousse_FR.txt"
#define MOTS_SIMPLE "misc/mots/liste_mots_simple_FR.txt"
#define MOTS_COMPLEX "misc/mots/liste_mots_FR.txt"

#define LISTE_MOTS MOTS_CLASSIQUE



#define CAPACITY 64

#define NB_TOUR 6

#define X_START_TAB 50
#define Y_START_TAB 100

#define SIZE_SLOT 50 // px
#define SIZE_BANNED_LETTERS 30 // px





using namespace std;

using BS = bitset<CAPACITY>;

enum PLACEMENT{KO, OK, WELL};

void get_list_words(const string nomFichier, vector<string>& liste_mots);

int count_num_words_in_list(const string nomFichier);

string getWord(const int pos, const string nomFichier);

string randomWord(const string nomFichier);

array<PLACEMENT, CAPACITY> compareWords(const vector<char> input, const string mot, const array<int, 26> alphabet);

void start_game(const string liste, string& mot, size_t& size_word, double& x_start_tab, array<int, 26>& alphabet, vector<vector<Texture*>>& tabs_slots, Window& window);

bool verif_word_exist(const vector<char> mot, const unordered_set<string> dico);

void trim(string& s);

void animJumpSlots(Window& window, const size_t tour, vector<vector<Texture*>>& tabs_slots);
#endif