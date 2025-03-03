#ifndef structure_hpp
#define structure_hpp

#include <SDL2/SDL_rect.h>
#include <iostream>
#include <string>

#include "systems/core/TextureManager.hpp"
#include "map/Tile.hpp"
#include "Texture.hpp"

class TextureManager;
class Camera;
class Entity;
class CollisionManager;
class Map;
class Player;
class TickManager;

class Structure
{
public:
    Structure() : Structure(nullptr, -1, -1, 0, false, nullptr, nullptr) {}
    Structure(Texture *texture, float x, float y, int HP, bool solid, Player *placedBy, TickManager *tickManager) : texture(texture), x(x), y(y), width(1), height(1), HP(HP), solid(solid), destroyed(false) {}
    ~Structure();

    void update();
    void destroy();
    void render(Camera *camera);
    void onCollision(Entity *entity);
    virtual void onLeftClick();
    virtual void onRightClick();

    SDL_FRect getHitBox();
    int getHP();
    bool isSolid();
    bool isDestroyed();
    void setX(float x);
    void setY(float y);
    void setHitBox(SDL_FRect hitBox);
    void setTexture(Texture *texture);
    static std::string getName() { return "Structure"; };
    static int getTexture()
    {
        std::cout << "ERROR: default Structure::getTexture() should not be used" << std::endl;
        return -1;
    };
    virtual std::string getClassName() = 0;
    float getPositionX();
    float getPositionY();

protected:
    Texture *texture;
    float x, y;
    float width, height;
    bool solid;
    unsigned int HP;
    bool destroyed;

    int getTileSize();
};

#endif
