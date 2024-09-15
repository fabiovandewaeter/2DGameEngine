#ifndef static_object_hpp
#define static_object_hpp

#include "../Texture.hpp"
#include "../systems/Camera.hpp"

class StaticObject
{
public:
    StaticObject();
    StaticObject(Texture *texture, SDL_Rect hitBox, const char *name, unsigned int HP);
    ~StaticObject();

    void init(Texture *texture, SDL_Rect hitBox, const char *name, unsigned int HP);

    void destroy();
    void render(Camera *camera);

    SDL_Rect getHitBox();
    bool isSolid();

private:
    Texture *texture;
    SDL_Rect hitBox;
    bool solid;

    const char *name;
    unsigned int HP;
};

#endif