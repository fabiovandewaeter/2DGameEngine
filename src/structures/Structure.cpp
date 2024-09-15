#include "Structure.hpp"

Structure::Structure(){}
Structure::Structure(Texture *texture, std::string name, unsigned int HP){
    init(texture, (SDL_Rect){0, 0, 0, 0}, name, HP);
}
Structure::Structure(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP){

    init(texture, hitBox, name, HP);
}
Structure::~Structure(){}

void Structure::init(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP){
    this->texture = texture;
    this->hitBox = hitBox;
    this->name = name;
    this->HP = HP;
}
void Structure::setHitBox(SDL_Rect hitBox){
    this->hitBox = hitBox;
}