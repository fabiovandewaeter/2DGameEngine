#ifndef map_hpp
#define map_hpp

#define CHUNK_SIZE 16

#include "SDL2/SDL_rect.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>

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
    void render(Player *player);
    void update();

    bool checkRectanglesCollision(SDL_FRect rectA, SDL_FRect rectB);
    bool isPointInCollisionWithRectangle(float x, float y, SDL_FRect rect);
    bool isRectangleInCollisionWithSolidStructure(SDL_FRect rect);
    SDL_FRect handleCollisionsForEntity(Entity *entity, float newPosX, float newPosY);
    void addPlayer(Player *player);
    void addEntity(Entity *entity);

    bool isChunkGenerated(int x, int y);
    Chunk *getChunk(int x, int y);
    int getTileSize();
    int getChunkSize();
    EntityManager *getEntityManager();

private:
    int tileSize;
    TextureManager *textureManager;
    PerlinNoise *perlinNoise;
    CollisionManager *collisionManager;
    std::unordered_map<std::string, Chunk *> allChunks;
    std::vector<Chunk *> nearbyChunks;
    EntityManager *entityManager;

    void convertToChunkCoordinates(int &x, int &y);
    void generateChunk(int positionX, int positionY);
    void loadSquareMap(int size);
};

#endif
