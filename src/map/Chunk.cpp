#include "Chunk.hpp"

Chunk::Chunk(int positionX, int positionY, int tileSize, Texture *tileTextures, Texture *staticObjectTextures)
{
    this->positionX;
    this->positionY;
    this->tileSize = tileSize;
    this->tileTextures = tileTextures;
    this->staticObjectTextures = staticObjectTextures;
    this->box = (SDL_Rect){positionX, positionY, tileSize * SIZE, tileSize * SIZE};
    loadTiles();
    loadStaticObjects();
}
Chunk::~Chunk()
{
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        delete this->tiles[i];
    }
    int size = this->staticObjects.size();
    for (int i = 0; i < size; i++)
    {
        delete this->staticObjects[i];
    }
}

void Chunk::loadTiles()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            this->tiles[16 * i + j] = new Tile(&this->tileTextures[0], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize});
        }
    }
}
void Chunk::loadStaticObjects()
{
    int i = 0, j = 0;
    this->staticObjects.push_back(new Wall(&this->staticObjectTextures[0], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize}));
    i++;
    this->staticObjects.push_back(new Wall(&this->staticObjectTextures[1], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize}));
    i++;
}

void Chunk::render(SDL_Renderer *renderer, Camera *camera)
{
    SDL_Rect renderBox = this->box;
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        for (int i = 0; i < SIZE * SIZE; i++)
        {
            this->tiles[i]->render(renderer, camera);
        }
        int size = this->staticObjects.size();
        for (int i = 0; i < size; i++){
            this->staticObjects[i]->render(renderer, camera);
        }
    }
}