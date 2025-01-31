#ifndef structure_hpp
#define structure_hpp

#include <SDL2/SDL_rect.h>
#include <iostream>
#include <string>

#include "systems/core/TextureManager.hpp"
#include "map/Tile.hpp"

class TextureManager;
class Texture;
class Material;
class Camera;
class Entity;
class CollisionManager;
class Map;

class Structure
{
public:
    Structure() : Structure(nullptr, {0, 0, 0, 0}, nullptr, false) {}
    Structure(Texture *texture, int x, int y, const Material *material, bool solid) : Structure(texture, {x, y, getTileSize(), getTileSize()}, material, solid) {}
    Structure(Texture *texture, SDL_Rect hitBox, const Material *material, bool solid) : texture(texture), hitBox(hitBox), material(material), HP(HP), solid(solid), destroyed(false) {}
    ~Structure();

    void update();
    void destroy();
    void render(Camera *camera);
    void onCollision(Entity *entity);
    virtual void onLeftClick();
    virtual void onRightClick();

    SDL_Rect getHitBox();
    int getHP();
    bool isSolid();
    bool isDestroyed();
    void setHitBox(SDL_Rect hitBox);
    static std::string getName() { return "Structure"; };
    static int getTexture()
    {
        std::cout << "ERROR: default Structure::getTexture() should not be used" << std::endl;
        return -1;
    };

protected:
    Texture *texture;
    SDL_Rect hitBox;
    const Material *material;
    bool solid;
    unsigned int HP;
    bool destroyed;

    int getTileSize();
};

#endif
