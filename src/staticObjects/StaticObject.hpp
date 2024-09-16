#ifndef static_object_hpp
#define static_object_hpp

#include "../Texture.hpp"
#include "../systems/Camera.hpp"

class StaticObject
{
public:
    StaticObject();
    StaticObject(Texture *texture, std::string name, unsigned int HP);
    StaticObject(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP);
    ~StaticObject();

    void init(Texture *texture, SDL_Rect hitBox, std::string name, unsigned int HP);

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