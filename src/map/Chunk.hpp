#ifndef chunk_hpp
#define chunk_hpp

#define SIZE 16

#include <vector>
#include <unordered_map>
#include <cmath>
#include "Tile.hpp"
#include "../structures/Structure.hpp"
#include "../structures/passiveStructures/Wall.hpp"
#include "../systems/PerlinNoise.hpp"

class Tile;

class Chunk
{
public:
    Chunk(int positionX, int positionY, int tileSize, std::vector<Texture *> *tileTextures, std::vector<Texture *> *passiveStructureTextures, std::vector<Texture *> *activeStructureTextures, PerlinNoise *perlinNoise);
    ~Chunk();

    void loadTiles();
    void loadTilesWithPerlinNoise();
    void loadPassiveStructures();
    void loadActiveStructures();
    void render(Camera *camera);

    Tile *getTile(int x, int y);
    Structure *getPassiveStructure(int x, int y);
    Structure *getActiveStructure(int x, int y);
    bool isPassiveStructure(int x, int y);
    bool isActiveStructure(int x, int y);
    void addPassiveStructure(int x, int y, Structure *passiveStructure);
    void addActiveStructure(int x, int y, Structure *activeStructure);
    void addWall(int x, int y);
    void destroyPassiveStructure(int x, int y);

private:
    Tile *allTiles[SIZE * SIZE];
    std::vector<Texture *> *tileTextures;
    int tileSize;

    std::unordered_map<std::string, Structure *> allPassiveStructures, allActiveStructures;
    std::vector<Texture *> *passiveStructureTextures, *activeStructureTextures;

    int positionX, positionY;
    SDL_Rect box;
    PerlinNoise *perlinNoise;

    void convertToTileCoordinates(int &x, int &y);
};

#endif