#include "motus.h"
#include "librairies.h"


using namespace std;

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


    while(getline (file_words_list, selected_word))
        nb_lines++;


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
 * 
 * @return Bitset qui indique quelles lettres sont bien placées
 */
vector<int> compareWords(const string input, const string mot, const array<int, 26> alphabet, set<char>& banned_letters){
 
    vector<int> res;
    array<int, 26> temp_alphabet{};
    temp_alphabet = alphabet;


    // On vérifie les lettres bien placées
    for(size_t i=0; i<mot.length()-1; i++){
        if(input[i] == mot[i]){ // La lettre est bien placée
            res.push_back(OK);
            temp_alphabet[((int)input[i])-97]--;
        }
    }    

    // On test les lettres mal placée
    for(size_t i=0; i<mot.length()-1; i++){ 
        if(input[i] != mot[i]){ // la lettre n'est pas au bon endroit
            if(temp_alphabet.at(((int)input[i])-97) > 0){ // la lettre est dans le mot
                temp_alphabet[((int)input[i])-97]--;

                res.push_back(WELL); 
            }
            else{ // la lettre n'est pas dans le mot
                res.push_back(KO);

                banned_letters.insert(input[i]);
            }
        }
    }
            
   

    return res;
}