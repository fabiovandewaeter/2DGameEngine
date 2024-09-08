#ifndef map_hpp
#define map_hpp

#include <vector>
#include "Tile.hpp"
#include "../systems/Camera.hpp"
#include "../systems/TextureManager.hpp"

class Map
{
public:
    Map();
    ~Map();

    void init(Texture *tileTextures);
    void loadTiles();
    void render(SDL_Renderer *renderer, Camera *camera);

private:
    std::vector<Tile*> tiles;
    int tileSize;
    Texture *tileTextures;
};

#endif