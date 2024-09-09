#include "Map.hpp"

Map::Map() {}
Map::~Map()
{
    for (auto &pair : this->allChunks)
    {
        delete pair.second;
    }
    this->nearbyChunks.clear();
    this->allChunks.clear();
}

void Map::init(Texture *tileTextures, Texture *staticObjectTextures)
{
    this->tileTextures = tileTextures;
    this->staticObjectTextures = staticObjectTextures;
    loadChunks();
}

void Map::loadChunks()
{
    //generateChunk(TILE_SIZE * CHUNK_SIZE * 0, 0 * TILE_SIZE * CHUNK_SIZE);
}

void Map::generateChunk(int positionX, int positionY)
{
    Chunk *newChunk = new Chunk(positionX, positionY, TILE_SIZE, this->tileTextures, this->staticObjectTextures);
    this->nearbyChunks.push_back(newChunk);

    int i = positionX, j = positionY;
    convertToChunkCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    this->allChunks[coordinates] = newChunk;
    std::cout << "Chunk generated at (" << coordinates << ") | Total: " << this->allChunks.size() << std::endl;
}

void Map::render(SDL_Renderer *renderer, Camera *camera)
{
    int size = this->nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        this->nearbyChunks[i]->render(renderer, camera);
    }
}

void Map::convertToChunkCoordinates(int &x, int &y)
{
    x = std::floor(static_cast<float>(x) / CHUNK_SIZE / TILE_SIZE);
    y = std::floor(static_cast<float>(y) / CHUNK_SIZE / TILE_SIZE);
}

// returns the chunk that contains the coordinates ; generates the chunk if it is not already done
Chunk *Map::getChunk(int x, int y)
{
    int i = x, j = y;
    convertToChunkCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);

    if (this->allChunks.find(coordinates) == this->allChunks.end())
    {
        generateChunk(i * TILE_SIZE * CHUNK_SIZE, j * TILE_SIZE * CHUNK_SIZE);
    }
    return this->allChunks[coordinates];
}