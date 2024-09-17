#ifndef structure_hpp
#define structure_hpp

#include "../Texture.hpp"
#include "../systems/Camera.hpp"

struct description{
    std::string name;
    std::string details;
};

class Structure
{
public:
    Structure();
    /*Structure(Texture *texture, unsigned int HP, bool solid);
    Structure(Texture *texture, SDL_Rect hitBox, unsigned int HP, bool solid);*/
    ~Structure();

    void init(Texture *texture, unsigned int HP, bool solid);
    void init(Texture *texture, SDL_Rect hitBox, unsigned int HP, bool solid);

    void destroy();
    void render(Camera *camera);

    SDL_Rect getHitBox();
    void setHitBox(SDL_Rect hitBox);
    bool isSolid();

private:
    Texture *texture;
    SDL_Rect hitBox;
    bool solid;
    unsigned int HP;
    description description;
};

#endif