#ifndef wall_hpp
#define wall_hpp

#include "StaticObject.hpp"

class Wall : public StaticObject
{
public:
    Wall(Texture *texture, SDL_Rect hitBox);
    ~Wall();

private:
};

#endif