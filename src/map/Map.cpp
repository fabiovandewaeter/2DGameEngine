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
    /*int x = 0, y = 0;
    int deltaPixels = this->tileSize;

    this->nearbyChunks.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){0, 0, this->tileSize, this->tileSize}));

    int p = 100;

    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->nearbyChunks.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){i * this->tileSize, j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }
    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->nearbyChunks.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){-i * this->tileSize, -j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }
    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->nearbyChunks.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){-i * this->tileSize, j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }
    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->nearbyChunks.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){i * this->tileSize, -j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }

    for (int i = 1; i < p; i++)
    {
        this->nearbyChunks.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){i * this->tileSize, 0, this->tileSize, this->tileSize}));
    }
    for (int i = 1; i < p; i++)
    {
        this->nearbyChunks.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){0, i * this->tileSize, this->tileSize, this->tileSize}));
    }
    for (int i = 1; i < p; i++)
    {
        this->nearbyChunks.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){-i * this->tileSize, 0, this->tileSize, this->tileSize}));
    }
    for (int i = 1; i < p; i++)
    {
        this->nearbyChunks.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){0, -i * this->tileSize, this->tileSize, this->tileSize}));
    }*/
   int n = 1;
   
    generateChunk(TILE_SIZE, TILE_SIZE);
}

void Map::generateChunk(int positionX, int positionY){
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