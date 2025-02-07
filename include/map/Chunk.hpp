#ifndef chunk_hpp
#define chunk_hpp

#define SIZE 16

#include <SDL2/SDL_rect.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

#include <functional> // for std::hash

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
    Chunk(int positionX, int positionY, int tileSize, Map *map, TextureManager *textureManager, PerlinNoise *perlinNoise, CollisionManager *collisionManager);
    ~Chunk();

    void loadTiles();
    void loadTilesDefault();
    void loadTilesWithPerlinNoise();
    void loadPassiveStructures();
    void loadActiveStructures();
    void render(Camera *camera);
    void update();

    Tile *getTile(int x, int y);
    Structure *getStructure(int x, int y);
    bool isStructure(int x, int y);
    void addStructure(Structure *structure);
    void destroyStructure(int x, int y);
    void setFaction(Faction *faction);

private:
    Tile *allTiles[SIZE * SIZE];
    TextureManager *textureManager;
    int tileSize;

    Map *map;
    std::unordered_map<std::pair<int, int>, Structure *, hash_pair> updatableStructures;
    std::unordered_map<std::pair<int, int>, Structure *, hash_pair> otherStructures;

    int positionX, positionY;
    SDL_Rect box;
    PerlinNoise *perlinNoise;

    Faction *faction;

    void convertToTileCoordinates(int &x, int &y);
};

#endif
