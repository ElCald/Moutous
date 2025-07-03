#include "librairies.h"
#include "motus.h"

using namespace std;

int main(int argc, char* argv[]){

    string mot = randomWord(LISTE_MOTS);

    array<int, 26> alphabet{}; // Tableau du nombre de lettre de l'alphabet dans le mot
    set<char> banned_letters;

    // On remplit le tableau pour savoir quelles lettres font partit du mot
    for(size_t i=0; i<(mot.length()-1); i++){
        alphabet[((int)mot[i])-97] += 1;
    }
    
    cout << mot << endl;

    string myWord;

    do{
        cin >> myWord;
    }while(myWord.length() != mot.length()-1);
    
    vector<int> res = compareWords(myWord, mot, alphabet, banned_letters);

    int i=0;
    for(int r : res){
        if(r == OK)
            cout << mot[i];
        else if(r == WELL)
            cout << "^";
        else
            cout << "_";
        i++;
    }
    cout << endl;


    // cout << ((int)mot[0])-97 << endl;

    // cout << mot.length()-1 << endl;

    // for(size_t i=0; i<26; i++){
    //     cout << alphabet.at(i);
    // }
    // cout << endl;


    cin.get();
    return EXIT_SUCCESS;
}