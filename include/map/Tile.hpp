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
    Tile(std::string textureName, float positionX, float positionY) : textureName(textureName), positionX(positionX), positionY(positionY), mineableResource(Tile::defaultMineableResource) {}
    Tile(std::string textureName, float positionX, float positionY, Item *mineableResource) : textureName(textureName), positionX(positionX), positionY(positionY), mineableResource(mineableResource) {}
    ~Tile() = default;

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
    float positionX, positionY;
    static Item *defaultMineableResource;
    Item *mineableResource;
};

#endif
