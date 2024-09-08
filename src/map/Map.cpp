#include "Map.hpp"

Map::Map() {}
Map::~Map()
{
    int size = this->allChunks.size();
    for (int i = 0; i < size; i++)
    {
        delete this->allChunks[i];
    }
    this->nearbyChunks.clear();
    this->allChunks.clear();
}

void Map::init(Texture *tileTextures)
{
    this->tileTextures = tileTextures;
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
    for (int j = 1; j < number+1; j++)
    {
        int i = 0;
        // haut-droite
        for (int k = 0; k < number; k++)
        {
            generateChunk(TILE_SIZE * CHUNK_SIZE * i, -j * TILE_SIZE * CHUNK_SIZE);
            i++;
        }
    }
    for (int j = 1; j < number+1; j++)
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
    this->nearbyChunks.push_back(new Chunk(positionX, positionY, TILE_SIZE, this->tileTextures));
}

void Map::render(SDL_Renderer *renderer, Camera *camera)
{
    int size = this->nearbyChunks.size();
    for (int i = 0; i < size; i++)
    {
        this->nearbyChunks[i]->render(renderer, camera);
    }
}