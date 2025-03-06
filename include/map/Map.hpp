#ifndef map_hpp
#define map_hpp

#include "SDL2/SDL_rect.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include <memory>

#include "systems/utils/Constants.hpp"
#include "systems/CollisionManager.hpp"
#include "systems/game_objects/EntityManager.hpp"

class TextureManager;
class Texture;
class PerlinNoise;
class Chunk;
class TickManager;
class StructureFactory;
class Camera;
class Player;
class Entity;
class Structure;

class Map
{
public:
    Map(TickManager *tickManager, StructureFactory *structureFactory, PerlinNoise *perlinNoise) : tickManager(tickManager), structureFactory(structureFactory), perlinNoise(perlinNoise), collisionManager(new CollisionManager(this)), entityManager(new EntityManager(this)) { loadChunks(); }
    ~Map();

    void loadChunks();
    // render Chunk and Entities
    void render(Camera *camera);
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
    TickManager *getTickManager();
    StructureFactory *getStructureFactory();
    Structure *findClosestStructure(const std::string structureClassName, const Entity *entity);
    Entity *findClosestEnemy(const Entity *entity);

private:
    PerlinNoise *perlinNoise;
    CollisionManager *collisionManager;
    std::unordered_map<std::pair<int, int>, Chunk *, hash_pair> allChunks;
    std::vector<Chunk *> nearbyChunks;
    EntityManager *entityManager;
    TickManager *tickManager;
    StructureFactory *structureFactory;

    // return the coordinates of the Chunk that contains the coordiantes (x, y)
    std::pair<int, int> convertToChunkCoordinates(float x, float y);
    void generateChunk(float positionX, float positionY);
    void loadSquareMap(int size);
};

#endif
