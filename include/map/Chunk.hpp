#ifndef chunk_hpp
#define chunk_hpp

#include <SDL2/SDL_rect.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <functional> // for std::hash

#include "systems/utils/Constants.hpp"

struct hash_pair
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};

class Map;
class TextureManager;
class Texture;
class PerlinNoise;
class CollisionManager;
class Camera;
class Tile;
class Structure;
class Faction;

class Chunk
{
public:
    Chunk(int positionX, int positionY, Map *map, TextureManager *textureManager, PerlinNoise *perlinNoise, CollisionManager *collisionManager);
    ~Chunk();

    void loadTiles();
    void loadTilesDefault();
    void loadTilesWithPerlinNoise();
    void loadUpdatableStructures();
    void loadOtherStructures();
    void render(Camera *camera);
    void update();

    Tile *getTile(float x, float y);
    Structure *getStructure(float x, float y);
    bool isStructure(float x, float y);
    void addStructure(Structure *structure, float x, float y);
    void destroyStructure(float x, float y);
    void setFaction(Faction *faction);

private:
    Tile *allTiles[CHUNK_SIZE * CHUNK_SIZE];
    TextureManager *textureManager;

    Map *map;
    std::unordered_map<std::pair<int, int>, Structure *, hash_pair> updatableStructures;
    std::unordered_map<std::pair<int, int>, Structure *, hash_pair> otherStructures;

    float positionX, positionY;
    int width, height;
    PerlinNoise *perlinNoise;

    Faction *faction;

    // convert global in game coordinates to coordinates of the Tile in the Chunk
    std::pair<int, int> convertToLocalTileCoordinates(float x, float y);
};

#endif
