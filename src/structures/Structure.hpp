#ifndef structure_hpp
#define structure_hpp

#include "../Texture.hpp"
#include "../systems/Camera.hpp"

class Structure
{
public:
    Structure();
    Structure(Texture *texture, std::string name, unsigned int HP);
    Structure(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP);
    ~Structure();

    void init(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP);
    void setHitBox(SDL_Rect hitBox);
    void render(Camera *camera);
private:
    Texture *texture;
    SDL_Rect hitBox;
    std::string name;
    unsigned int HP;
};

#endif