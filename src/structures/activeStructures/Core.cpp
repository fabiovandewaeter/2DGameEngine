#include "Core.hpp"

Core::Core(Texture *texture, std::string name, unsigned int HP, bool solid){
    init(texture, (SDL_Rect){0, 0, 0, 0}, name, HP, solid);
}
Core::Core(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP, bool solid){

    init(texture, hitBox, name, HP, solid);
}