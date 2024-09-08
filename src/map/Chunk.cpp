#include "Chunk.hpp"

Chunk::Chunk(int positionX, int positionY, int tileSize, Texture *tileTextures)
{
    this->positionX;
    this->positionY;
    this->tileSize = tileSize;
    this->tileTextures = tileTextures;
    this->box = (SDL_Rect){positionX, positionY, tileSize * SIZE, tileSize * SIZE};
    loadTiles();
}
Chunk::~Chunk() {}

void Chunk::loadTiles()
{
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        this->tiles[i] = new Tile(&this->tileTextures[0], (SDL_Rect){0, 0, this->tileSize, this->tileSize});
    }
}

void Chunk::render(SDL_Renderer *renderer, Camera *camera)
{
    SDL_Rect renderBox = this->box;
    if (camera->isVisible(renderBox))
    {
        for (int i = 0; i < SIZE * SIZE; i++)
        {
            this->tiles[i]->render(renderer, camera);
        }
    }
}