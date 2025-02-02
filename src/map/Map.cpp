#include "map/Map.hpp"

#include <iostream>
#include "map/Chunk.hpp"

#include "systems/CollisionManager.hpp"
#include "systems/game_objects/EntityManager.hpp"
#include "entities/Player.hpp"

Map::Map(int tileSize, TextureManager *textureManager, PerlinNoise *perlinNoise) : tileSize(tileSize), textureManager(textureManager), perlinNoise(perlinNoise), collisionManager(new CollisionManager(this)), entityManager(new EntityManager(this)) { loadChunks(); }
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
    int step = CHUNK_SIZE * this->tileSize;
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

void Map::generateChunk(int positionX, int positionY)
{
    Chunk *newChunk = new Chunk(positionX, positionY, this->tileSize, this, this->textureManager, this->perlinNoise, this->collisionManager);
    this->nearbyChunks.push_back(newChunk);
    int i = positionX, j = positionY;
    convertToChunkCoordinates(i, j);
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

bool Map::checkRectanglesCollision(SDL_Rect rectA, SDL_Rect rectB) { return this->collisionManager->checkRectanglesCollision(rectA, rectB); }
bool Map::isPointInCollisionWithRectangle(int x, int y, SDL_Rect rect) { return this->collisionManager->isPointInCollisionWithRectangle(x, y, rect); }
bool Map::isRectangleInCollisionWithSolidStructure(SDL_Rect rect) { return this->collisionManager->isRectangleInCollisionWithSolidStructure(rect); }
SDL_Rect Map::handleCollisionsForEntity(Entity *entity, int newPosX, int newPosY)
{
    return this->collisionManager->handleCollisionsForEntity(entity, newPosX, newPosY);
}
void Map::addPlayer(Player *player) { this->entityManager->addPlayer(player); }
void Map::addEntity(Entity *entity) { this->entityManager->addEntity(entity); }

void Map::convertToChunkCoordinates(int &x, int &y)
{
    x = std::floor(static_cast<float>(x) / (CHUNK_SIZE * this->tileSize));
    y = std::floor(static_cast<float>(y) / (CHUNK_SIZE * this->tileSize));
}

// returns true if the chunk exist
bool Map::isChunkGenerated(int x, int y)
{
    return true;
    int i = x, j = y;
    convertToChunkCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);

    if (this->allChunks.find(coordinates) == this->allChunks.end())
    {
        return false;
    }
    return true;
}

// returns the chunk that contains the coordinates ; generates the chunk if it is not already done
Chunk *Map::getChunk(int x, int y)
{
    int i = x, j = y;
    convertToChunkCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);

    if (this->allChunks.find(coordinates) == this->allChunks.end())
    {
        generateChunk(i * this->tileSize * CHUNK_SIZE, j * this->tileSize * CHUNK_SIZE);
        std::cout << "Chunk generated at (" << coordinates << ") | Total: " << this->allChunks.size() << std::endl;
    }
    return this->allChunks[coordinates];
}
int Map::getTileSize()
{
    return this->tileSize;
}
int Map::getChunkSize()
{
    return CHUNK_SIZE;
}
EntityManager *Map::getEntityManager() { return this->entityManager; }
