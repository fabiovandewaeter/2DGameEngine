#include "map/Map.hpp"

#include <iostream>
#include "map/Chunk.hpp"

Map::Map() {}
Map::~Map()
{
    free();
}

void Map::init(Camera *camera, int tileSize, std::vector<Texture *> *tileTextures, std::vector<Texture *> *staticObjectTextures, std::vector<Texture *> *structureTextures, PerlinNoise *perlinNoise, CollisionManager *collisionManager)
{
    this->camera = camera;
    this->tileSize = tileSize;
    this->tileTextures = tileTextures;
    this->staticObjectTextures = staticObjectTextures;
    this->structureTextures = structureTextures;
    this->perlinNoise = perlinNoise;
    this->collisionManager = collisionManager;
    loadChunks();
}

void Map::loadChunks()
{
    loadSquareMap(20);
}
void Map::loadSquareMap(int size)
{
    int step = CHUNK_SIZE * this->tileSize;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            generateChunk(i * step-(step*size/2), j * step-(step*size/2));
        }
    }
}

void Map::generateChunk(int positionX, int positionY)
{
    Chunk *newChunk = new Chunk(positionX, positionY, this->tileSize, this, this->tileTextures, this->staticObjectTextures, this->structureTextures, this->perlinNoise, this->collisionManager);
    this->nearbyChunks.push_back(newChunk);
    int i = positionX, j = positionY;
    convertToChunkCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    this->allChunks[coordinates] = newChunk;
}

void Map::render()
{
    int size = this->nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        this->nearbyChunks[i]->render(this->camera);
    }
}
void Map::update()
{
    int size = this->nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        this->nearbyChunks[i]->update();
    }
}
void Map::free()
{
    for (auto &pair : this->allChunks)
    {
        delete pair.second;
    }
    this->allChunks.clear();
    this->nearbyChunks.clear();
}

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
