#ifndef chunk_hpp
#define chunk_hpp

#include <SDL2/SDL_rect.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <functional> // for std::hash
#include <memory>

#include "systems/utils/Constants.hpp"

class Map;
class TextureManager;
class Texture;
class PerlinNoise;
class CollisionManager;
class Camera;
class Tile;
class Structure;
class Faction;
class Entity;

class Chunk
{
public:
    Chunk(int positionX, int positionY, Map *map, PerlinNoise *perlinNoise, CollisionManager *collisionManager);
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
    // destroy the Structure and remove it from the Game
    void destroyStructure(float x, float y);
    // break the Structure and returns it
    Structure *breakStructure(float x, float y);
    void setFaction(Faction *faction);
    std::unique_ptr<std::pair<float, float>> findStructure(const std::string structureClassName, const Entity *entity);

private:
    Tile *allTiles[CHUNK_TILE_SIZE * CHUNK_TILE_SIZE];

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
