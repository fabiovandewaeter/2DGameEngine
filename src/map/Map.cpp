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
    int number = 100;
    for (int j = 0; j < number; j++)
    {
        int i = 0;
        // bas-droite
        for (int k = 0; k < number; k++)
        {
            generateChunk(TILE_SIZE * CHUNK_SIZE * i, j * TILE_SIZE * CHUNK_SIZE);
            i++;
        }
    }
    for (int j = 1; j < number + 1; j++)
    {
        int i = 0;
        // haut-droite
        for (int k = 0; k < number; k++)
        {
            generateChunk(TILE_SIZE * CHUNK_SIZE * i, -j * TILE_SIZE * CHUNK_SIZE);
            i++;
        }
    }
    for (int j = 1; j < number + 1; j++)
    {
        int i = 1;
        // haut-gauche
        for (int k = 0; k < number; k++)
        {
            generateChunk(-TILE_SIZE * CHUNK_SIZE * i, -j * TILE_SIZE * CHUNK_SIZE);
            i++;
        }
    }
    for (int j = 0; j < number; j++)
    {
        int i = 1;
        // bas-gauche
        for (int k = 0; k < number; k++)
        {
            generateChunk(-TILE_SIZE * CHUNK_SIZE * i, j * TILE_SIZE * CHUNK_SIZE);
            i++;
        }
    }
}

void Map::generateChunk(int positionX, int positionY)
{
    Chunk *newChunk = new Chunk(positionX, positionY, TILE_SIZE, this->tileTextures, this->staticObjectTextures);
    this->nearbyChunks.push_back(newChunk);

    int i = positionX, j = positionY;
    convertToChunkCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    //std::string coordinates = std::to_string(positionX) + "," + std::to_string(positionY);
    this->allChunks[coordinates] = newChunk;
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
    int i = x / (TILE_SIZE * CHUNK_SIZE);
    int j = y / (TILE_SIZE * CHUNK_SIZE);
    if (x < 0)
    {
        i -= 1;
    }
    if (y < 0)
    {
        j -= 1;
    }
    x = i;
    y = j;
}

// returns the chunk that contains the coordinates ; generates the chunk if it is not already done
Chunk *Map::getChunk(int x, int y)
{
    // (TILE_SIZE*CHUNKE_SIZE*i, TILE_SIZE*CHUNK_SIZE*j)                        (TILE_SIZE*CHUNKE_SIZE*i + TILE_SIZE*CHUNK_SIZE, TILE_SIZE*CHUNKE_SIZE*j)
    // (TILE_SIZE*CHUNKE_SIZE*i, TILE_SIZE*CHUNKE_SIZE*j + TILE_SIZE*CHUNK_SIZE)     (TILE_SIZE*CHUNKE_SIZE*i + TILE_SIZE*CHUNK_SIZE, TILE_SIZE*CHUNKE_SIZE*j + TILE_SIZE*CHUNK_SIZE)

    int i = x, j = y;
    convertToChunkCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);

    if (this->allChunks.find(coordinates) == this->allChunks.end())
    {
        printf("?????\n");
        generateChunk(x, y);
    }
    return this->allChunks[coordinates];
}