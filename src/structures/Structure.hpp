#ifndef structure_hpp
#define structure_hpp

#include "../Texture.hpp"

class Structure
{
public:
    Structure();
    Structure(Texture *texture, SDL_Rect hitBox, const char *name, unsigned int HP);
    ~Structure();

private:
    Texture *texture;
};

#endif