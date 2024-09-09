#ifndef chunk_hpp
#define chunk_hpp

#define SIZE 16

#include <vector>
#include "Tile.hpp"
#include "../objects/staticObjects/StaticObject.hpp"
#include "../objects/staticObjects/Wall.hpp"

class Tile;

class Chunk
{
public:
    Chunk(int positionX, int positionY, int tileSize, Texture *tileTextures, Texture *staticObjectTextures);
    ~Chunk();

    void render(SDL_Renderer *renderer, Camera *camera);
    void loadTiles();
    void loadStaticObjects();

private:
    Tile *tiles[SIZE * SIZE];
    Texture *tileTextures;
    int tileSize;

    std::vector<StaticObject *> staticObjects;
    Texture *staticObjectTextures;

    int positionX, positionY;
    SDL_Rect box;
};

#endif