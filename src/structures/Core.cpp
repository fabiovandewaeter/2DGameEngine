#include "Core.hpp"

Core::Core(Texture *texture, std::string name, unsigned int HP){
    init(texture, (SDL_Rect){0, 0, 0, 0}, name, HP);
}
Core::Core(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP){

    init(texture, hitBox, name, HP);
}