#ifndef tile_hpp
#define tile_hpp

#include <SDL2/SDL_rect.h>
#include <vector>
#include <string>

#include "systems/utils/Constants.hpp"

class Texture;
class Camera;
class Item;

class Tile
{
public:
    Tile(std::string textureName, float x, float y) : textureName(textureName), x(x), y(x), mineableResource(Tile::defaultMineableResource) {}
    Tile(std::string textureName, float x, float y, Item *mineableResource) : textureName(textureName), x(x), y(x), mineableResource(mineableResource) {}
    ~Tile();

    void render(Camera *camera);
    float getPositionX() const;
    float getPositionY() const;
    float getCenterX() const;
    float getCenterY() const;
    static int getTileSize();
    Item *getMineableResource() const;
    std::string getTextureName() const;

private:
    std::string textureName;
    float x, y;
    static Item *defaultMineableResource;
    Item *mineableResource;
};

#endif
