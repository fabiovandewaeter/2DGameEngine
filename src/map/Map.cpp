#include "Map.hpp"

Map::Map() {}
Map::~Map()
{
    int size = this->allTiles.size();

    for (int i = 0; i < size; i++)
    {
        delete this->allTiles[i];
    }
    this->updatedTiles.clear();
    this->allTiles.clear();
}

void Map::init(Texture *tileTextures)
{
    this->tileSize = 16;
    this->tileTextures = tileTextures;
    loadTiles();
}

void Map::loadTiles()
{
    int x = 0, y = 0;
    int deltaPixels = this->tileSize;

    this->updatedTiles.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){0, 0, this->tileSize, this->tileSize}));

    int p = 100;

    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->updatedTiles.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){i * this->tileSize, j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }
    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->updatedTiles.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){-i * this->tileSize, -j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }
    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->updatedTiles.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){-i * this->tileSize, j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }
    for (int j = 1; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            this->updatedTiles.push_back(new Tile(&this->tileTextures[1], (SDL_Rect){i * this->tileSize, -j * this->tileSize, this->tileSize, this->tileSize}));
        }
    }

    for (int i = 1; i < p; i++)
    {
        this->updatedTiles.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){i * this->tileSize, 0, this->tileSize, this->tileSize}));
    }
    for (int i = 1; i < p; i++)
    {
        this->updatedTiles.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){0, i * this->tileSize, this->tileSize, this->tileSize}));
    }
    for (int i = 1; i < p; i++)
    {
        this->updatedTiles.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){-i * this->tileSize, 0, this->tileSize, this->tileSize}));
    }
    for (int i = 1; i < p; i++)
    {
        this->updatedTiles.push_back(new Tile(&this->tileTextures[0], (SDL_Rect){0, -i * this->tileSize, this->tileSize, this->tileSize}));
    }
}

void Map::render(SDL_Renderer *renderer, Camera *camera)
{
    int size = this->updatedTiles.size();

    for (int i = 0; i < size; i++)
    {
        this->updatedTiles[i]->render(renderer, camera);
    }
}