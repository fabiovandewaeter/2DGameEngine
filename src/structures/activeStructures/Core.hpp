#ifndef core_hpp
#define core_hpp

#include "../Structure.hpp"

class Core : public Structure
{
public:
    Core(Texture *texture, unsigned int HP);
    Core(Texture *texture, SDL_Rect hitBox, unsigned int HP);

private:
};

#endif