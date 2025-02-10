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
    Tile(Texture *texture, int x, int y);
    Tile(Texture *texture, int x, int y, Item *mineableResource);
    ~Tile();

    void render(Camera *camera);
    int getCenterX();
    int getCenterY();
    int getTextureId();
    static int getTileSize();
    Item *getMineableResource();

private:
    Texture *texture;
    int x, y;
    static Item *defaultMineableResource;
    Item *mineableResource;
};

#endif
