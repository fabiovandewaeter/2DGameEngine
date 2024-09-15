#ifndef chunk_hpp
#define chunk_hpp

#define SIZE 16

#include <vector>
#include <unordered_map>
#include <cmath>
#include "Tile.hpp"
#include "../staticObjects/StaticObject.hpp"
#include "../staticObjects/Wall.hpp"
#include "../systems/PerlinNoise.hpp"

class Tile;

class Chunk
{
public:
    Chunk(int positionX, int positionY, int tileSize, std::vector<Texture *> *tileTextures, std::vector<Texture *> *staticObjectTextures, PerlinNoise *perlinNoise);
    ~Chunk();

    void loadTiles();
    void loadTilesWithPerlinNoise();
    void loadStaticObjects();
    void render(Camera *camera);

    void convertToTileCoordinates(int &x, int &y);
    Tile *getTile(int x, int y);
    bool isStaticObject(int x, int y);
    StaticObject *getStaticObject(int x, int y);
    void addStaticObject(int x, int y);
    void destroyStaticObject(int x, int y);

private:
    Tile *allTiles[SIZE * SIZE];
    std::vector<Texture *> *tileTextures;
    int tileSize;

    std::unordered_map<std::string, StaticObject *> allStaticObjects;
    std::vector<Texture *> *staticObjectTextures;

    int positionX, positionY;
    SDL_Rect box;
    PerlinNoise *perlinNoise;
};

#endif