#include "librairies.h"
#include "game.h"
#include "utiles.h"

using namespace std;

int Objet::compteur_id = 0;

int main(int argc, char* argv[]){


    Uint32 frameStart;
    int frameTime;
    size_t keyboard_cursor = 1; // case dans laquelle le clavier écrit
    size_t size_word = 0;
    double x_start_tab = 0;
    int x_start_banned = (WIN_WIDTH/2) - (520/2);
    int y_start_banned = WIN_HEIGHT - 150;
    int tour = 0;
    bool victoire = false;
    bool failed = false;
    string mot;

    array<int, 26> alphabet{}; // Tableau du nombre de lettre de l'alphabet dans le mot

    vector<string> liste_mots; // liste de tous les mots (complexes) pour vérification

    vector<vector<Texture*>> tabs_slots; // Tableau des cases de lettres
    vector<Texture*> tab_lettres_clavier; // Contient toutes les lettres du clavier

    vector<char> my_word; // Mot entré par l'utilisateur

    vector<string> noms_fichiers_lettres {"lettre_A.bmp", "lettre_B.bmp", "lettre_C.bmp", "lettre_D.bmp", "lettre_E.bmp", "lettre_F.bmp", "lettre_G.bmp", "lettre_H.bmp",
                                        "lettre_I.bmp", "lettre_J.bmp", "lettre_K.bmp", "lettre_L.bmp", "lettre_M.bmp", "lettre_N.bmp", "lettre_O.bmp", "lettre_P.bmp",
                                        "lettre_Q.bmp", "lettre_R.bmp", "lettre_S.bmp", "lettre_T.bmp", "lettre_U.bmp", "lettre_V.bmp", "lettre_W.bmp", "lettre_X.bmp",
                                        "lettre_Y.bmp", "lettre_Z.bmp"};
    
    // Textures lettres
    vector<Texture*> textures_slot; // Contient toutes les lettres classiques et à la fin le slot
    vector<Texture*> textures_slot_correctes; // Contient toutes les lettres correctes
    vector<Texture*> textures_slot_placements; // Contient toutes les lettres placements
    vector<Texture*> textures_lettre_banned; // Contient toutes les lettres bannies


    Uint32 last_update = SDL_GetTicks();

    // Création de la fenêtre
    Window window(WIN_WIDTH, WIN_HEIGHT);

    // Écran de chargement
    Texture background_load(window, string(TEXTURE_BACKGROUND_LOAD), WIN_WIDTH, WIN_HEIGHT, 0, 0);
    window.setTextureBackground(&background_load);

    window.render();


    Texture background(window, string(TEXTURE_BACKGROUND), WIN_WIDTH, WIN_HEIGHT, 0, 0);
    window.setTextureBackground(&background);

    Texture motus_logo(window, string(TEXTURE_LOGO), 448, 64, (WIN_WIDTH/2)-(448/2), 20);
    window.addTextureScene(&motus_logo);

    window.addTextZones(1, 10, WIN_HEIGHT-H4-10);


    // Chargement des textures des lettres
    for(int i=0; i<26; i++){
        textures_slot.push_back(new Texture(window, string(REP_CLASSIQUES) + noms_fichiers_lettres.at(i), SIZE_SLOT, SIZE_SLOT, 0, 0));
        textures_slot_correctes.push_back(new Texture(window, string(REP_CORRECTES) + noms_fichiers_lettres.at(i), SIZE_SLOT, SIZE_SLOT, 0, 0));
        textures_slot_placements.push_back(new Texture(window, string(REP_PLACEMENTS) + noms_fichiers_lettres.at(i), SIZE_SLOT, SIZE_SLOT, 0, 0));
        textures_lettre_banned.push_back(new Texture(window, string(REP_INCORRECTES) + noms_fichiers_lettres.at(i), SIZE_SLOT, SIZE_SLOT, 0, 0));
    }

    textures_slot.push_back(new Texture(window, string(TEXTURE_SLOT), SIZE_SLOT, SIZE_SLOT, 0, 0));


    for(int i=0; i<26; i++){
        tab_lettres_clavier.push_back(new Texture(window, string(REP_CLASSIQUES) + noms_fichiers_lettres.at(i), SIZE_BANNED_LETTERS, SIZE_BANNED_LETTERS, x_start_banned+((SIZE_BANNED_LETTERS+10)*(i%13)), y_start_banned+((SIZE_BANNED_LETTERS+10)*( (i>12)?1:0 ))));
    }

    for(auto t : tab_lettres_clavier){
        window.addTextureBanned(t);
    }


    get_list_words(MOTS_COMPLEX, liste_mots); // liste de mots complexes pour vérification

    unordered_set<string> dictionnaire_mots(liste_mots.begin(), liste_mots.end()); // Création d'un dictionnaire à partir de cette liste
    
    start_game(MOTS_CLASSIQUE, mot, size_word, x_start_tab, alphabet, tabs_slots, window);
    // printf("%s\n", mot.c_str());
    window.updateText(0, "Mot : " + mot);

    // initialisation du mot de l'utilisateur
    my_word.push_back(mot[0]);
    tabs_slots[tour][0]->texture = textures_slot.at(((int)mot[0])-97)->texture;


    SDL_Keycode key;

    while(window.program_launched){

        frameStart = SDL_GetTicks(); // Temps au début de la frame

        while(SDL_PollEvent(&window.event)){

            switch(window.event.type){
                case SDL_KEYDOWN: // gestion du clavier appui de la touche

                    key = window.event.key.keysym.sym;

                    // Appuis sur une lettre entre A et Z
                    if (!victoire && !failed && tour < NB_TOUR && key >= SDLK_a && key <= SDLK_z && keyboard_cursor < size_word) {
                        char lettre = 'a';
                        switch (key) {
                            case SDLK_a:
                                lettre = 'a';
                                break;
                            case SDLK_b:
                                lettre = 'b';
                                break;
                            case SDLK_c:
                                lettre = 'c';
                                break;
                            case SDLK_d:
                                lettre = 'd';
                                break;
                            case SDLK_e:
                                lettre = 'e';
                                break;
                            case SDLK_f:
                                lettre = 'f';
                                break;
                            case SDLK_g:
                                lettre = 'g';
                                break;
                            case SDLK_h:
                                lettre = 'h';
                                break;
                            case SDLK_i:
                                lettre = 'i';
                                break;
                            case SDLK_j:
                                lettre = 'j';
                                break;
                            case SDLK_k:
                                lettre = 'k';
                                break;
                            case SDLK_l:
                                lettre = 'l';
                                break;
                            case SDLK_m:
                                lettre = 'm';
                                break;
                            case SDLK_n:
                                lettre = 'n';
                                break;
                            case SDLK_o:
                                lettre = 'o';
                                break;
                            case SDLK_p:
                                lettre = 'p';
                                break;
                            case SDLK_q:
                                lettre = 'q';
                                break;
                            case SDLK_r:
                                lettre = 'r';
                                break;
                            case SDLK_s:
                                lettre = 's';
                                break;
                            case SDLK_t:
                                lettre = 't';
                                break;
                            case SDLK_u:
                                lettre = 'u';
                                break;
                            case SDLK_v:
                                lettre = 'v';
                                break;
                            case SDLK_w:
                                lettre = 'w';
                                break;
                            case SDLK_x:
                                lettre = 'x';
                                break;
                            case SDLK_y:
                                lettre = 'y';
                                break;
                            case SDLK_z:
                                lettre = 'z';
                                break;
                            default:
                                continue;
                        }
                        
                        // On attribut à la case du tableau la texture de la lettre correspondante
                        tabs_slots[tour][keyboard_cursor]->texture = textures_slot.at(((int)lettre)-97)->texture;
                        my_word.push_back(lettre);
                        keyboard_cursor++;
                    }

                    switch (window.event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            window.program_launched = SDL_FALSE;
                            break;

                        case SDLK_SPACE:
                    
                            window.hideTextZones();

                            start_game(MOTS_CLASSIQUE, mot, size_word, x_start_tab, alphabet, tabs_slots, window);
                            // printf("%s\n", mot.c_str());

                            my_word.clear();
                            keyboard_cursor = 1;
                            victoire = false;
                            failed = false;
                            tour = 0;

                            // initialisation du mot de l'utilisateur
                            my_word.push_back(mot[0]);
                            tabs_slots[tour][0]->texture = textures_slot.at(((int)mot[0])-97)->texture;

                            for(int i=0; i<26; i++){
                                tab_lettres_clavier[i]->texture = textures_slot.at(i)->texture;
                            }

                            window.updateText(0, "Mot : " + mot);

                            break;

                        case SDLK_BACKSPACE:
                            // Suppression d'une lettre tant qu'on est pas à la case 0
                            if(keyboard_cursor > 1){
                                keyboard_cursor--;
                                my_word.pop_back();
                                tabs_slots[tour][keyboard_cursor]->texture = textures_slot.at(26)->texture;
                            }
                            break;

                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            if(!victoire && tour < NB_TOUR && keyboard_cursor == size_word){

                                if(verif_word_exist(my_word, dictionnaire_mots)){
                                    victoire = true;

                                    array<PLACEMENT, CAPACITY> res = compareWords(my_word, mot, alphabet);

                                    for(size_t i=0; i<mot.length(); i++){
                                        if(res.at(i) == OK){
                                            tabs_slots[tour][i]->texture = textures_slot_correctes.at(((int)my_word[i])-97)->texture;
                                        }else if(res.at(i) == WELL){
                                            tabs_slots[tour][i]->texture = textures_slot_placements.at(((int)my_word[i])-97)->texture;
                                            victoire = false;
                                        }else{
                                            victoire = false;
                                        }

                                        // remplissage du clavier
                                        if(res.at(i) == KO && tab_lettres_clavier[((int)my_word[i])-97]->texture != textures_slot_correctes.at(((int)my_word[i])-97)->texture){
                                            tab_lettres_clavier[((int)my_word[i])-97]->texture = textures_lettre_banned.at(((int)my_word[i])-97)->texture;
                                        }else if(res.at(i) == WELL && tab_lettres_clavier[((int)my_word[i])-97]->texture != textures_slot_correctes.at(((int)my_word[i])-97)->texture){
                                            tab_lettres_clavier[((int)my_word[i])-97]->texture = textures_slot_placements.at(((int)my_word[i])-97)->texture;
                                        }else{
                                            tab_lettres_clavier[((int)my_word[i])-97]->texture = textures_slot_correctes.at(((int)my_word[i])-97)->texture;
                                        }
                                    }

                                    if(!victoire && tour < NB_TOUR-1){
                                        my_word.clear();

                                        tour++;

                                        my_word.push_back(mot[0]);
                                        tabs_slots[tour][0]->texture = textures_slot.at(((int)mot[0])-97)->texture;

                                        animJumpSlots(window, tour-1, tabs_slots);
                                    }else{
                                        failed = true;
                                        window.showTextZones();

                                        animJumpSlots(window, tour, tabs_slots);
                                    }

                                    keyboard_cursor = 1;

                                    
                                }
                                else{

                                }
                            }
                            break;

                        case SDLK_TAB:
                            window.showTextZones();
                            break;

                        default:
                            continue;
                    }
                    
                    break;

                case SDL_KEYUP: // gestion du clavier levé de la touche
                    switch (window.event.key.keysym.sym) {
                        case SDLK_TAB:
                            window.hideTextZones();
                            break;

                        default:
                            continue;
                    }
                    break;

                case SDL_QUIT: // clique sur la croix de la fenêtre
                    window.program_launched = SDL_FALSE; break;
                
                default:
                    break;
            }

        }//fin boucle event


        last_update = window.animate(last_update);

        window.render();


        // --- Contrôle du temps de frame ---
        frameTime = SDL_GetTicks() - frameStart;

        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }



    SDL_Quit(); 

    #ifdef _DEBUG_
    cout << "Fin de prog" << endl;
    #endif


    cin.get();
    return EXIT_SUCCESS;
}