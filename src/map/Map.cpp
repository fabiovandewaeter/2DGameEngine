#include "map/Map.hpp"

#include <iostream>

#include "map/Chunk.hpp"
#include "entities/Player.hpp"

Map::~Map()
{
    delete collisionManager;
    for (auto &pair : allChunks)
    {
        delete pair.second;
    }
    allChunks.clear();
    nearbyChunks.clear();
    delete entityManager;
}

void Map::loadChunks()
{
    loadSquareMap(2);
}

void Map::loadSquareMap(int size)
{
    int step = CHUNK_TILE_SIZE;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            generateChunk(i * step, j * step);
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            generateChunk(-i * step - step, j * step);
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            generateChunk(i * step, -j * step - step);
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            generateChunk(-i * step - step, -j * step - step);
        }
    }
}

void Map::generateChunk(float positionX, float positionY)
{
    Chunk *newChunk = new Chunk(positionX, positionY, this, perlinNoise, collisionManager);
    nearbyChunks.push_back(newChunk);
    std::pair<float, float> newCoordinates = {positionX, positionY};
    allChunks[newCoordinates] = newChunk;
}

void Map::render(Camera *camera)
{
    int size = nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        nearbyChunks[i]->render(camera);
    }
    entityManager->render(camera);
}

void Map::update()
{
    int size = nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        nearbyChunks[i]->update();
    }
    entityManager->update();
}

bool Map::checkRectanglesCollision(SDL_FRect rectA, SDL_FRect rectB) { return collisionManager->checkRectanglesCollision(rectA, rectB); }
bool Map::isPointInCollisionWithRectangle(float positionX, float positionY, SDL_FRect rect) { return collisionManager->isPointInCollisionWithRectangle(positionX, positionY, rect); }
bool Map::isRectangleInCollisionWithSolidStructure(SDL_FRect rect) { return collisionManager->isRectangleInCollisionWithSolidStructure(rect); }
SDL_FRect Map::handleCollisionsForEntity(Entity *entity, float newPosX, float newPosY) { return collisionManager->handleCollisionsForEntity(entity, newPosX, newPosY); }
void Map::addPlayer(Player *player) { entityManager->addPlayer(player); }
void Map::addEntity(Entity *entity) { entityManager->addEntity(entity); }

std::pair<int, int> Map::convertToChunkCoordinates(float positionX, float positionY)
{
    int chunkX = static_cast<int>(std::floor(positionX / CHUNK_TILE_SIZE));
    int chunkY = static_cast<int>(std::floor(positionY / CHUNK_TILE_SIZE));
    return {chunkX * CHUNK_TILE_SIZE, chunkY * CHUNK_TILE_SIZE};
}

// returns true if the chunk exist
bool Map::isChunkGenerated(float positionX, float positionY)
{
    std::pair<int, int> newCoordinates = convertToChunkCoordinates(positionX, positionY);
    if (allChunks.find(newCoordinates) == allChunks.end())
    {
        return false;
    }
    return true;
}

// returns the chunk that contains the coordinates ; generates the chunk if it is not already done
Chunk *Map::getChunk(float positionX, float positionY)
{
    std::pair<int, int> newCoordinates = convertToChunkCoordinates(positionX, positionY);
    if (allChunks.find(newCoordinates) == allChunks.end())
    {
        generateChunk(newCoordinates.first, newCoordinates.second);
        std::cout << "Chunk generated at (" << newCoordinates.first << "," << newCoordinates.second << ") | Total: " << allChunks.size() << std::endl;
    }
    return allChunks[newCoordinates];
}

int Map::getChunkSize() { return CHUNK_TILE_SIZE; }
TickManager *Map::getTickManager() { return tickManager; }
EntityManager *Map::getEntityManager() { return entityManager; }
StructureFactory *Map::getStructureFactory() { return structureFactory; }

Structure *Map::findClosestStructure(const std::string structureClassName, const Entity *entity)
{
    Structure *res;
    for (auto &chunkPair : allChunks)
    {
        Chunk *chunk = chunkPair.second;
        res = chunk->findClosestStructure(structureClassName, entity);
        if (res != nullptr)
        {
            return res;
        }
    }
    return nullptr;
}

Entity *Map::findClosestEnemy(const Entity *entity) { return entityManager->findClosestEnemy(entity); }
