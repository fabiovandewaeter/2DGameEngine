#include "map/Map.hpp"

#include <iostream>

#include "map/Chunk.hpp"
#include "entities/Player.hpp"

Map::~Map()
{
    for (auto &pair : this->allChunks)
    {
        delete pair.second;
    }
    this->allChunks.clear();
    this->nearbyChunks.clear();
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
    Chunk *newChunk = new Chunk(positionX, positionY, this, this->perlinNoise, this->collisionManager);
    this->nearbyChunks.push_back(newChunk);
    std::pair<float, float> newCoordinates = {positionX, positionY};
    this->allChunks[newCoordinates] = newChunk;
}

void Map::render(Player *player)
{
    int size = this->nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        this->nearbyChunks[i]->render(player->getCamera());
    }
    this->entityManager->render(player->getCamera());
}

void Map::update()
{
    int size = this->nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        this->nearbyChunks[i]->update();
    }
    this->entityManager->update();
}

bool Map::checkRectanglesCollision(SDL_FRect rectA, SDL_FRect rectB) { return this->collisionManager->checkRectanglesCollision(rectA, rectB); }
bool Map::isPointInCollisionWithRectangle(float x, float y, SDL_FRect rect) { return this->collisionManager->isPointInCollisionWithRectangle(x, y, rect); }
bool Map::isRectangleInCollisionWithSolidStructure(SDL_FRect rect) { return this->collisionManager->isRectangleInCollisionWithSolidStructure(rect); }
SDL_FRect Map::handleCollisionsForEntity(Entity *entity, float newPosX, float newPosY) { return this->collisionManager->handleCollisionsForEntity(entity, newPosX, newPosY); }
void Map::addPlayer(Player *player) { this->entityManager->addPlayer(player); }
void Map::addEntity(Entity *entity) { this->entityManager->addEntity(entity); }

std::pair<int, int> Map::convertToChunkCoordinates(float x, float y)
{
    int chunkX = static_cast<int>(std::floor(x / CHUNK_TILE_SIZE));
    int chunkY = static_cast<int>(std::floor(y / CHUNK_TILE_SIZE));
    return {chunkX * CHUNK_TILE_SIZE, chunkY * CHUNK_TILE_SIZE};
}

// returns true if the chunk exist
bool Map::isChunkGenerated(float x, float y)
{
    std::pair<int, int> newCoordinates = convertToChunkCoordinates(x, y);
    if (this->allChunks.find(newCoordinates) == this->allChunks.end())
    {
        return false;
    }
    return true;
}

// returns the chunk that contains the coordinates ; generates the chunk if it is not already done
Chunk *Map::getChunk(float x, float y)
{
    std::pair<int, int> newCoordinates = convertToChunkCoordinates(x, y);
    // std::pair<int, int> newCoordinates = {x, y};

    if (this->allChunks.find(newCoordinates) == this->allChunks.end())
    {
        generateChunk(newCoordinates.first, newCoordinates.second);
        std::cout << "Chunk generated at (" << newCoordinates.first << "," << newCoordinates.second << ") | Total: " << this->allChunks.size() << std::endl;
    }
    return this->allChunks[newCoordinates];
}

int Map::getChunkSize() { return CHUNK_TILE_SIZE; }
TickManager *Map::getTickManager() { return this->tickManager; }
EntityManager *Map::getEntityManager() { return this->entityManager; }
StructureFactory *Map::getStructureFactory() { return this->structureFactory; }

std::unique_ptr<std::pair<float, float>> Map::findStructure(const std::string structureClassName, const Entity *entity)
{
    std::unique_ptr<std::pair<float, float>> res;
    for (auto &chunkPair : allChunks)
    {
        Chunk *chunk = chunkPair.second;
        res = chunk->findStructure(structureClassName, entity);
        if (res != nullptr)
        {
            return res;
        }
    }
    return nullptr;
}
