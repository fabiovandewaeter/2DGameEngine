#ifndef static_object_hpp
#define static_object_hpp

#include "../../Texture.hpp"
#include "../../systems/Camera.hpp"

class StaticObject
{
public:
    StaticObject();
    StaticObject(Texture *texture, SDL_Rect hitBox);
    ~StaticObject();
    
    void init(Texture *texture, SDL_Rect hitBox);

    void destroy();
    void render(SDL_Renderer *renderer, Camera *camera);

    SDL_Rect getHitBox();
    bool isSolid();

private:
    Texture *texture;
    SDL_Rect hitBox;
    bool solid;
};

#endif