#include "Chunk.hpp"

Chunk::Chunk(int positionX, int positionY, int tileSize, Texture *tileTextures, Texture *staticObjectTextures, PerlinNoise *perlinNoise)
{
    this->positionX;
    this->positionY;
    this->tileSize = tileSize;
    this->tileTextures = tileTextures;
    this->staticObjectTextures = staticObjectTextures;
    this->box = (SDL_Rect){positionX, positionY, tileSize * SIZE, tileSize * SIZE};
    this->perlinNoise = perlinNoise;
    // loadTiles();
    loadTilesWithPerlinNoise();
    loadStaticObjects();
}
Chunk::~Chunk()
{
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        delete this->allTiles[i];
    }
    for (auto &pair : this->allStaticObjects)
    {
        delete pair.second;
    }
}

void Chunk::loadTiles()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            this->allTiles[SIZE * i + j] = new Tile(&this->tileTextures[0], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize});
        }
    }
}
void Chunk::loadTilesWithPerlinNoise()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int x = i * this->tileSize + this->box.x;
            int y = j * this->tileSize + this->box.y;
            double res = this->perlinNoise->perlin2d(x, y, 0.001f, 1);
            int textureIndex = 0;
            int numberOfTileTextures = 4;
            if (res < 1.0 / numberOfTileTextures)
            {
                textureIndex = 0;
            }
            else if (res < 2 * (1.0 / numberOfTileTextures))
            {
                textureIndex = 1;
            }
            else if (res < 3 * (1.0 / numberOfTileTextures))
            {
                textureIndex = 2;
            }
            else if (res < 4 * (1.0 / numberOfTileTextures))
            {
                textureIndex = 3;
            }
            this->allTiles[SIZE * i + j] = new Tile(&this->tileTextures[textureIndex], (SDL_Rect){x, y, this->tileSize, this->tileSize});
        }
    }
}
void Chunk::loadStaticObjects()
{
    int i = 2, j = 0;
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    this->allStaticObjects[coordinates] = new Wall(&this->staticObjectTextures[0], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize});
    i++;
    i++;
    coordinates = std::to_string(i) + "," + std::to_string(j);
    this->allStaticObjects[coordinates] = new Wall(&this->staticObjectTextures[1], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize});
    i++;
    i++;
    int x = 2 * this->tileSize, y = 0 * this->tileSize;
    // convertToTileCoordinates(x, y);
}

void Chunk::render(SDL_Renderer *renderer, Camera *camera)
{
    SDL_Rect renderBox = this->box;
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        for (int i = 0; i < SIZE * SIZE; i++)
        {
            this->allTiles[i]->render(renderer, camera);
        }
    }
    for (auto &pair : this->allStaticObjects)
    {
        pair.second->render(renderer, camera);
    }
}

void Chunk::convertToTileCoordinates(int &x, int &y)
{
    x = static_cast<int>(std::floor(static_cast<float>(x) / this->tileSize)) % SIZE;
    y = static_cast<int>(std::floor(static_cast<float>(y) / this->tileSize)) % SIZE;
    if (x < 0)
    {
        x = SIZE + x;
    }
    if (y < 0)
    {
        y = SIZE + y;
    }
}
// returns the tile that contains the coordinates
Tile *Chunk::getTile(int x, int y)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    return this->allTiles[SIZE * i + j];
}
bool Chunk::isStaticObject(int x, int y)
{
    int i = x, j = y;
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    if (this->allStaticObjects.find(coordinates) == this->allStaticObjects.end())
    {
        return false;
    }
    return true;
}
StaticObject *Chunk::getStaticObject(int x, int y)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    return this->allStaticObjects[coordinates];
}
void Chunk::addStaticObject(int x, int y)
{
    if (!isStaticObject(x, y))
    {
        int i = x, j = y;
        std::string coordinates = std::to_string(i) + "," + std::to_string(j);
        this->allStaticObjects[coordinates] = new Wall(&this->staticObjectTextures[1], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize});
    }
}
void Chunk::destroyStaticObject(int x, int y)
{
    if (isStaticObject(x, y))
    {
        int i = x, j = y;
        std::string coordinates = std::to_string(i) + "," + std::to_string(j);
        this->allStaticObjects[coordinates]->destroy();
        this->allStaticObjects.erase(coordinates);
    }
}