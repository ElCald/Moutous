#include "librairies.h"

#include "utiles.h"

/// Window

/**
 * Constructeur d'une fenêtre SDL2.
 * Initialisation vidéo uniquement.
 * Création de la fenêtre et du renderer.
 * 
 * @param _win_width Largeur de la fenêtre
 * @param _win_height Hauteur de la fenêtre
 */
Window::Window(const size_t _win_width, const size_t _win_height) : win_width(_win_width), win_height(_win_height) {

    #ifdef _DEBUG_
    SDL_version v;
    SDL_VERSION(&v);
    printf("SDL version : %d.%d.%d\n", v.major, v.minor, v.patch);
    #endif

    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
        ExitWithError("Initialisation SDL");

    if( SDL_CreateWindowAndRenderer(win_width, win_height, SDL_WINDOW_SHOWN, &fenetre, &renderer) != 0 )
        ExitWithError("Creation fenetre et rendu echouee");

    program_launched = SDL_TRUE;

    // Police d'écriture
    if (TTF_Init() != 0) 
        ExitWithError("Erreur TTF_Init");

    font = TTF_OpenFont(POLICE_ARIAL, H6);

    if (!font) 
        ExitWithError("Erreur TTF_OpenFont");
    

    center_win_width = win_width/2;
    center_win_height = win_height/2;

    #ifdef _DEBUG_
    cout << "Fenêtre crée" << endl;
    #endif
}


Window::~Window(){

    for(Texture* t : texture_scene){
        SDL_DestroyTexture(t->texture);
    }

    #ifdef _DEBUG_
    cout << "Destruction des textures" << endl;
    #endif

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);

    #ifdef _DEBUG_
    cout << "Destruction de la window" << endl;
    #endif
}


void Window::ExitWithError(string msg){
    SDL_Log("Erreur : %s > %s\n", msg.c_str(), SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    exit(EXIT_FAILURE);
}


int Window::get_center_win_width(){
    return center_win_width;
}

int Window::get_center_win_height(){
    return center_win_height;
}


/**
 * Rendu des images de la fenêtre
 */
void Window::render(){
    SDL_RenderClear(renderer);

    // Rendu du fond
    for(Texture* t : texture_background){
        if(t == nullptr)
            continue;

        if( (SDL_RenderCopy(renderer, t->texture, NULL, t->position)) != 0 )
            ExitWithError("Erreur affichage image dans le rendu");

        #ifdef _DEBUG_
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
        SDL_RenderDrawRect(renderer, t->position);
        #endif

    }


    for(Texture* t : texture_scene){
        if(t == nullptr)
            continue;

        if( (SDL_RenderCopy(renderer, t->texture, NULL, t->position)) != 0 )
            ExitWithError("Erreur affichage image dans le rendu");

        #ifdef _DEBUG_
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
        SDL_RenderDrawRect(renderer, t->position);
        #endif

    }

    for(Texture* t : texture_slots){
        if(t == nullptr)
            continue;

        if( (SDL_RenderCopy(renderer, t->texture, NULL, t->position)) != 0 )
            ExitWithError("Erreur affichage image dans le rendu");

        #ifdef _DEBUG_
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
        SDL_RenderDrawRect(renderer, t->position);
        #endif

    }

     for(Texture* t : texture_banned){
        if(t == nullptr)
            continue;

        if( (SDL_RenderCopy(renderer, t->texture, NULL, t->position)) != 0 )
            ExitWithError("Erreur affichage image dans le rendu");

        #ifdef _DEBUG_
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
        SDL_RenderDrawRect(renderer, t->position);
        #endif

    }


    #ifdef _DEBUG_
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    #endif

    renderTexts();

    SDL_RenderPresent(renderer);
}


/**
 * Animation des personnages
 */
Uint32 Window::animate(Uint32 last_update){

    // Uint32 now = SDL_GetTicks();
    Uint32 new_last_update = last_update;

    // now - last_update >= FRAME_DELAY_ANIMATION



    return new_last_update;
}


/**
 * Ajout d'une texture à la scène
 */
void Window::addTexture(Texture* texture){
    texture_scene.push_back(texture);
}

/**
 * Ajout d'une texture aux slots
 */
void Window::addTextureSlots(Texture* texture){
    texture_slots.push_back(texture);
}

/**
 * Ajout d'une texture aux lettres banned
 */
void Window::addTextureBanned(Texture* texture){
    texture_banned.push_back(texture);
}


/**
 * Vide les textures des slots
 */
void Window::clearTextureSlots(){
    texture_slots.clear();
}

/**
 * Ajout d'une texture au background
 */
void Window::addTextureBackground(Texture* texture){
    texture_background.push_back(texture);
}


void Window::addText(const string& text, int x, int y, SDL_Color color) {
    texts.push_back(new TextElement(renderer, font, text, x, y, color));
}


/**
 * 
 * @param index Index dans la liste de textw
 */
void Window::updateText(size_t index, const string& newText) {
    if (index < texts.size())
        texts[index]->setText(newText);
}


void Window::renderTexts() {
    for (auto& t : texts)
        t->render(renderer);
}



/**
 * Crée le nombre de zones de textes souhaité 
 * @param num Nombre de zones de textes
 * @param x
 * @param y
 */
void Window::addTextZones(int num, const int x, const int y){

    for(int i=0; i<num; i++){
        addText("Test", x, y+TTF_FontHeight(font)*i, {255,255,255,255});
    }

}


void Window::addObjet(Objet* obj){
    objets_scene.push_back(obj);
}



/// TextElement

TextElement::TextElement(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) : texture(nullptr), font(font), currentText(text), color(color) {
    rect.x = x;
    rect.y = y;
    updateTexture(renderer);
}

TextElement::~TextElement() {
    if (texture)
        SDL_DestroyTexture(texture);
}

void TextElement::setText(const string& newText) {
    if (newText != currentText) {
        currentText = newText;
        if (texture)
            SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void TextElement::updateTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, currentText.c_str(), color);
    if (!surface) return;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);
}

void TextElement::render(SDL_Renderer* renderer) {
    if (!texture)
        updateTexture(renderer);

    if (texture)
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
}





/// Texture
/**
 * @param img Image bmp
 * @param _width Largeur de l'image
 * @param _height Hauteur de l'image
 * @param _x Position x
 * @param _y Position y
 */
Texture::Texture(Window& window, string img, const size_t _width, const size_t _height, const int _x, const int _y) {

    #ifdef _DEBUG_
    cout << "Chargement texture : " << img << endl;
    #endif

    SDL_Surface* image;

    position = new SDL_Rect;


    // Chargelent de l'image
    if( (image = SDL_LoadBMP(img.c_str())) == NULL )
        window.ExitWithError("Erreur du chargement de l'image : " + img);


    // Chargement de l'image dans une texture pour pouvoir l'afficher
    if( (texture = SDL_CreateTextureFromSurface(window.renderer, image)) == NULL ){
        SDL_FreeSurface(image);
        window.ExitWithError("Erreur du texturing : " + img);
    }


    SDL_FreeSurface(image); // Libération de la mémoire utilisé par l'image car on ne l'utilise plus


    // Emplacement de l'image dans notre fenêtre
    if( (SDL_QueryTexture(texture, NULL, NULL, &position->w, &position->h)) != 0 )
        window.ExitWithError("Erreur query texture : " + img);


    position->w = _width;
    position->h = _height;
    position->x = _x;
    position->y = _y;



    // Chargement de la texture contenant l'image dans le rendu pour l'affichage
    if( (SDL_RenderCopy(window.renderer , texture, NULL, position)) != 0 )
        window.ExitWithError("Erreur affichage image : " + img);

}



/**
 * @param img Image bmp
 * @param _width Largeur de l'image
 * @param _height Hauteur de l'image
 * @param _x Position x
 * @param _y Position y
 */
Texture::Texture(Window& window, string img, SDL_Rect* pos) {

    #ifdef _DEBUG_
    cout << "Chargement texture : " << img << endl;
    #endif

    SDL_Surface* image;

    position = new SDL_Rect;

    // Chargelent de l'image
    if( (image = SDL_LoadBMP(img.c_str())) == NULL )
        window.ExitWithError("Erreur du chargement de l'image : " + img);

    // Chargement de l'image dans une texture pour pouvoir l'afficher
    if( (texture = SDL_CreateTextureFromSurface(window.renderer, image)) == NULL ){
        SDL_FreeSurface(image);
        window.ExitWithError("Erreur du texturing : " + img);
    }

    SDL_FreeSurface(image); // Libération de la mémoire utilisé par l'image car on ne l'utilise plus

    // Emplacement de l'image dans notre fenêtre
    if( (SDL_QueryTexture(texture, NULL, NULL, &position->w, &position->h)) != 0 )
        window.ExitWithError("Erreur query texture : " + img);


    position = pos;
    


    // Chargement de la texture contenant l'image dans le rendu pour l'affichage
    if( (SDL_RenderCopy(window.renderer , texture, NULL, position)) != 0 )
        window.ExitWithError("Erreur affichage image : " + img);

}


Texture::~Texture(){}


void Texture::setPlace(int _x, int _y){
    position->x = _x;
    position->y = _y;
}

void Texture::setSize(int _width, int _height){
    position->w = _width;
    position->h = _height;
}



void Texture::setX(int _x){
    position->x = _x;
}

void Texture::setY(int _y){
    position->y = _y;
}

void Texture::addX(int _x){
    position->x += _x;
}

void Texture::addY(int _y){
    position->y += _y;
}






/// Objet

Objet::Objet(Window& window, string texture_path, const size_t width, const size_t height, const int _x, const int _y, const type_objet _type){
    id = compteur_id;
    compteur_id++;

    #ifdef _DEBUG_
    cout << "Création de l'objet id: " << id << endl;
    #endif

    type = _type;

    position = new SDL_Rect();

    position->w = width;
    position->h = height;
    position->x = _x;
    position->y = _y;

    texture = new Texture(window, texture_path, position);

    window.addTexture(texture);
}


Objet::~Objet(){}



