#ifndef structure_hpp
#define structure_hpp

#include "../Texture.hpp"
#include "../systems/Camera.hpp"

class Structure
{
public:
    Structure();
    Structure(Texture *texture, std::string name, unsigned int HP, bool solid);
    Structure(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP, bool solid);
    ~Structure();

    void init(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP, bool solid);

    void destroy();
    void render(Camera *camera);

    SDL_Rect getHitBox();
    void setHitBox(SDL_Rect hitBox);
    bool isSolid();

private:
    Texture *texture;
    SDL_Rect hitBox;
    bool solid;

    std::string name;
    unsigned int HP;
};

#endif