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
    Structure(std::string textureName, float positionX, float positionY, int HP, bool solid, Player *placedBy, TickManager *tickManager) : textureName(textureName), positionX(positionX), positionY(positionY), width(1), height(1), HP(HP), solid(solid), destroyed(false) {}
    ~Structure();

    void update();
    void destroy();
    void render(Camera *camera);
    void onCollision(Entity *entity);
    virtual void onLeftClick();
    virtual void onRightClick();

    bool isSolid() const;
    bool isDestroyed() const;

    // getter
    int getHP() const;
    float getPositionX() const;
    float getPositionY() const;
    SDL_FRect getHitBox() const;
    std::string getTextureName() const;
    virtual std::string getClassName() = 0;

    // setter
    void setX(float positionX);
    void setY(float positionY);
    void setHitBox(SDL_FRect hitBox);
    void setTextureName(std::string textureName);

protected:
    std::string textureName;
    float positionX, positionY;
    float width, height;
    bool solid;
    unsigned int HP;
    bool destroyed;

    int getTileSize();
};

#endif
