#ifndef wall_hpp
#define wall_hpp

#include "../Structure.hpp"

class Wall : public Structure
{
public:
    Wall(Texture *texture, unsigned int HP);
    Wall(Texture *texture, SDL_Rect hitBox, unsigned int HP);

private:
};

#endif