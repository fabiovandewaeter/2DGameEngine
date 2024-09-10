#ifndef map_hpp
#define map_hpp

#define TILE_SIZE 16
#define CHUNK_SIZE 16

#include <vector>
#include <unordered_map>
#include <cmath>
#include "Tile.hpp"
#include "Chunk.hpp"
#include "../systems/Camera.hpp"
#include "../systems/TextureManager.hpp"

class Map
{
public:
    Map();
    ~Map();

    void init(Texture *tileTextures, Texture *staticObjectTextures);
    void loadChunks();
    void generateChunk(int positionX, int positionY);
    void loadSquareMap(int size);
    void render(SDL_Renderer *renderer, Camera *camera);

    void convertToChunkCoordinates(int &x, int &y);
    Chunk *getChunk(int x, int y);

private:
    std::unordered_map<std::string, Chunk *> allChunks;
    std::vector<Chunk *> nearbyChunks;
    Texture *tileTextures;
    Texture *staticObjectTextures;
};

#endif