#ifndef wall_hpp
#define wall_hpp

#include "../Structure.hpp"

class Wall : public Structure
{
public:
    Wall(Texture *texture, SDL_Rect hitBox, bool solid);
    ~Wall();

private:
};

#endif