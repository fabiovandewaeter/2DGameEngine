#ifndef map_hpp
#define map_hpp

#include "SDL2/SDL_rect.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include <memory>

#include "systems/utils/Constants.hpp"

class TextureManager;
class Texture;
class PerlinNoise;
class CollisionManager;
class Chunk;
class EntityManager;
class Player;
class Entity;

class Map
{
public:
    Map(int tileSize, TextureManager *textureManager, PerlinNoise *perlinNoise);
    ~Map();

    void loadChunks();
    // render Chunk and Entities
    void render(Player *player);
    void update();

    bool checkRectanglesCollision(SDL_FRect rectA, SDL_FRect rectB);
    bool isPointInCollisionWithRectangle(float x, float y, SDL_FRect rect);
    bool isRectangleInCollisionWithSolidStructure(SDL_FRect rect);
    SDL_FRect handleCollisionsForEntity(Entity *entity, float newPosX, float newPosY);
    void addPlayer(Player *player);
    void addEntity(Entity *entity);

    bool isChunkGenerated(float x, float y);
    Chunk *getChunk(float x, float y);
    int getTileSize();
    int getChunkSize();
    EntityManager *getEntityManager();
    std::unique_ptr<std::pair<float, float>> findStructure(const std::string structureClassName, const Entity *entity);

private:
    TextureManager *textureManager;
    PerlinNoise *perlinNoise;
    CollisionManager *collisionManager;
    std::unordered_map<std::pair<int, int>, Chunk *, hash_pair> allChunks;
    std::vector<Chunk *> nearbyChunks;
    EntityManager *entityManager;

    // return the coordinates of the Chunk that contains the coordiantes (x, y)
    std::pair<int, int> convertToChunkCoordinates(float x, float y);
    void generateChunk(float positionX, float positionY);
    void loadSquareMap(int size);
};

#endif
