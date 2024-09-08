#ifndef map_hpp
#define map_hpp

#define TILE_SIZE 16
#define CHUNK_SIZE 16

#include <vector>
#include "Tile.hpp"
#include "Chunk.hpp"
#include "../systems/Camera.hpp"
#include "../systems/TextureManager.hpp"

class Map
{
public:
    Map();
    ~Map();

    void init(Texture *tileTextures);
    void loadChunks();
    void generateChunk(int positionX, int positionY);
    void render(SDL_Renderer *renderer, Camera *camera);

private:
    std::vector<Chunk *> allChunks;
    std::vector<Chunk *> nearbyChunks;
    Texture *tileTextures;
};

#endif