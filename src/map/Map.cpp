#include "map/Map.hpp"

#include <iostream>
#include "map/Chunk.hpp"

#include "systems/CollisionManager.hpp"
#include "systems/game_objects/EntityManager.hpp"
#include "entities/Player.hpp"

Map::Map(int tileSize, TextureManager *textureManager, PerlinNoise *perlinNoise) : textureManager(textureManager), perlinNoise(perlinNoise), collisionManager(new CollisionManager(this)), entityManager(new EntityManager(this)) { loadChunks(); }
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
    loadSquareMap(0);
}
void Map::loadSquareMap(int size)
{
    int step = CHUNK_SIZE;
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
    Chunk *newChunk = new Chunk(positionX, positionY, this, this->textureManager, this->perlinNoise, this->collisionManager);
    this->nearbyChunks.push_back(newChunk);
    std::pair<int, int> newCoordinates = convertToChunkCoordinates(positionX, positionY);
    int i = newCoordinates.first, j = newCoordinates.second;
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    this->allChunks[coordinates] = newChunk;
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
    int newX = std::floor(x / (CHUNK_SIZE));
    int newY = std::floor(y / (CHUNK_SIZE));
    if (x < 0){
        newX = newX - 1;
    }
    if (y < 0){
        newY = newY - 1;
    }
    std::pair<int, int> res = {newX, newY};
    return res;
}

// returns true if the chunk exist
bool Map::isChunkGenerated(float x, float y)
{
    std::pair<int, int> newCoordinates = convertToChunkCoordinates(x, y);
    int i = newCoordinates.first, j = newCoordinates.second;
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);

    if (this->allChunks.find(coordinates) == this->allChunks.end())
    {
        return false;
    }
    return true;
}

// returns the chunk that contains the coordinates ; generates the chunk if it is not already done
Chunk *Map::getChunk(float x, float y)
{
    std::pair<int, int> newCoordinates = convertToChunkCoordinates(x, y);
    int i = newCoordinates.first, j = newCoordinates.second;
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);

    if (this->allChunks.find(coordinates) == this->allChunks.end())
    {
        generateChunk(i * CHUNK_SIZE, j * CHUNK_SIZE);
        std::cout << "Chunk generated at (" << coordinates << ") | Total: " << this->allChunks.size() << std::endl;
    }
    return this->allChunks[coordinates];
}
int Map::getTileSize()
{
    return TILE_SIZE;
}
int Map::getChunkSize()
{
    return CHUNK_SIZE;
}
EntityManager *Map::getEntityManager() { return this->entityManager; }
