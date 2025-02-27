#ifndef tile_hpp
#define tile_hpp

#include <SDL2/SDL_rect.h>
#include <vector>

#include "systems/utils/Constants.hpp"

class Texture;
class Camera;
class Item;

class Tile
{
public:
    Tile(Texture *texture, float x, float y);
    Tile(Texture *texture, float x, float y, Item *mineableResource);
    ~Tile();

    void render(Camera *camera);
    float getCenterX();
    float getCenterY();
    int getTextureId();
    static int getTileSize();
    Item *getMineableResource();

private:
    Texture *texture;
    float x, y;
    static Item *defaultMineableResource;
    Item *mineableResource;
};

#endif
