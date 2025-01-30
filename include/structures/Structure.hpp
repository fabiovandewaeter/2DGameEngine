#ifndef structure_hpp
#define structure_hpp

#include <SDL2/SDL_rect.h>
#include <iostream>
#include <string>

class Texture;
class Camera;
class Entity;
class CollisionManager;
class Map;

class Structure
{
public:
    Structure();
    Structure(Texture *texture, SDL_Rect hitBox, unsigned int HP, bool solid);
    ~Structure();

    void update();
    void destroy();
    void render(Camera *camera);
    void onCollision(Entity *entity);
    virtual void onLeftClick();
    virtual void onRightClick();

    SDL_Rect getHitBox();
    bool isSolid();
    bool isDestroyed();
    void setHitBox(SDL_Rect hitBox);
    static std::string getName() { return "Structure"; };
    static int getTexture()
    {
        std::cout << "ERROR: default Structure::getTexture() should not be used" << std::endl;
        return -1;
    };

private:
    SDL_Rect hitBox;
    Texture *texture;
    bool solid;
    unsigned int HP;
    bool destroyed;
};

#endif
