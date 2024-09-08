#ifndef chunk_hpp
#define chunk_hpp

#define SIZE 16

#include <vector>
#include "Tile.hpp"

class Tile;

class Chunk
{
public:
    Chunk(int positionX, int positionY, int tileSize, Texture *tileTextures);
    ~Chunk();
    
    void render(SDL_Renderer *renderer, Camera *camera);
    void loadTiles();

private:
    Tile *tiles[SIZE*SIZE];
    Texture *tileTextures;
    int tileSize;
    int positionX, positionY;
    SDL_Rect box;
};

#endif