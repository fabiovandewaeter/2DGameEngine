#ifndef core_hpp
#define core_hpp

#include "../Structure.hpp"

class Core : public Structure
{
public:
    Core(Texture *texture, std::string name, unsigned int HP, bool solid);
    Core(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP, bool solid);

private:
};

#endif