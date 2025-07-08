#include "game.h"
#include "librairies.h"
#include "utiles.h"


using namespace std;


/**
 * 
 */
void get_list_words(const string nomFichier, vector<string>& liste_mots){
    ifstream file_words_list(nomFichier);
    string selected_word;

    
    if (!file_words_list.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier !" << endl;
        exit(EXIT_FAILURE);
    }


    while(getline (file_words_list, selected_word)){
        trim(selected_word);
        liste_mots.push_back(selected_word);
    }

    file_words_list.close();
}

/**
 * @param nomFichier Nom du fichier contenant la liste de mots
 * @return Le nombre de lignes du fichier
 */
int count_num_words_in_list(const string nomFichier){

    ifstream file_words_list(nomFichier);
    string selected_word;
    int nb_lines = 0;

    if (!file_words_list.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier !" << endl;
        exit(EXIT_FAILURE);
    }


    while(getline (file_words_list, selected_word)){
        nb_lines++;
    }
        

    file_words_list.close();

    return nb_lines;
}


/**
 * @param pos Indice du mot à récupérer dans la liste
 * @param nomFichier Nom du fichier contenant la liste de mots
 * @return Le nombre de lignes du fichier
 */
string getWord(const int pos, const string nomFichier){

    string selected_word;

    ifstream file_words_list(nomFichier);

    if (!file_words_list.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier !" << endl;
        exit(EXIT_FAILURE);
    }


    for(int i=0; i<pos; i++){
        if(!getline (file_words_list, selected_word)){
            cerr << "Hors liste" << endl;
            exit(EXIT_FAILURE);
        }
    }

    file_words_list.close();

    return selected_word;
}



/**
 * @return Mot aléatoire de la liste de mots
 */
string randomWord(const string nomFichier){

    int nbWords = count_num_words_in_list(nomFichier);

    random_device rd;                         // Source de hasard (non déterministe)
    mt19937 gen(rd());                        // Générateur Mersenne Twister
    uniform_int_distribution<> dist(1, nbWords);   // Bornes inclusives [1, 10]

    int i_randWord = dist(gen);

    
    string mot = getWord(i_randWord, nomFichier);

    return mot;

}


/**
 * @param input Mot entré par le joueur
 * @param mot Mot choisi dans la liste
 * @param alphabet Tableau qui contient les lettres et leur nombre dans le mot
 * @param banned_letters Set qui contient les lettres testées qui ne sont pas dans le mot
 * 
 * @return Tableau qui indique quelles lettres sont bien placées
 */
array<PLACEMENT, CAPACITY> compareWords(const vector<char> input, const string mot, const array<int, 26> alphabet, set<char>& banned_letters){
 
    array<PLACEMENT, CAPACITY> res{};
    array<int, 26> temp_alphabet{};
    temp_alphabet = alphabet;


    // On vérifie les lettres bien placées
    for(size_t i=0; i<mot.length(); i++){
        if(input[i] == mot[i]){ // La lettre est bien placée
            res[i] = OK;
            temp_alphabet[((int)input[i])-97]--;
        }
    }    

    // On test les lettres mal placée
    for(size_t i=0; i<mot.length(); i++){ 
        if(input[i] != mot[i]){ // la lettre n'est pas au bon endroit
            if(temp_alphabet.at(((int)input[i])-97) > 0){ // la lettre est dans le mot
                temp_alphabet[((int)input[i])-97]--;

                res[i] = WELL; 
            }
            else{ // la lettre n'est pas dans le mot
                res[i] = KO;

                banned_letters.insert(input[i]);
            }
        }
    }
            
   

    return res;
}



void start_game(const string liste, string& mot, size_t& size_word, double& x_start_tab, array<int, 26>& alphabet, vector<vector<Texture*>>& tabs_slots, Window& window){

    vector<Texture*> tab_slots;

    tabs_slots.clear();
    window.clearTextureSlots();

    mot = randomWord(liste);

    trim(mot);

    size_word = mot.length(); // Taille du mot 

    x_start_tab = (WIN_WIDTH/2) - ((double)size_word/2)*SIZE_SLOT;

    alphabet.fill(0);

    // On remplit le tableau pour savoir quelles lettres font partit du mot
    for(size_t i=0; i<size_word; i++){
        alphabet[((int)mot[i])-97] += 1;
    }

    for(size_t j=0; j<NB_TOUR; j++){
        tab_slots.clear();
        for(size_t i=0; i<size_word; i++){
            // Création des textures de slots
            tab_slots.push_back(new Texture(window, string(TEXTURE_SLOT), SIZE_SLOT, SIZE_SLOT, x_start_tab+(SIZE_SLOT*i), Y_START_TAB+(SIZE_SLOT*j)));
        }
        tabs_slots.push_back(tab_slots);
    }


    for(size_t j=0; j<NB_TOUR; j++){
        for(size_t i=0; i<size_word; i++){
            window.addTextureSlots(tabs_slots.at(j).at(i));
        }
    }


}

void trim(string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
        [](unsigned char ch) { return !isspace(ch); }));
    s.erase(find_if(s.rbegin(), s.rend(),
        [](unsigned char ch) { return !isspace(ch); }).base(), s.end());
}



/**
 * Vérifie si le mot écrit éxiste dans la liste de mots
 * 
 * @return true si le mot est dans la liste
 */
bool verif_word_exist(const vector<char> mot, const unordered_set<string> dico){
    string mon_mot(mot.begin(), mot.end());

    if (dico.find(mon_mot) != dico.end()) {
        return true;
    } 

    return false;
}