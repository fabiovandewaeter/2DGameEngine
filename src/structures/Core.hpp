#ifndef core_hpp
#define core_hpp

#include "Structure.hpp"

class Core : public Structure
{
public:
    Core(Texture *texture, SDL_Rect hitBox, const char *name, unsigned int HP);
    ~Core();
private:
};

#endif