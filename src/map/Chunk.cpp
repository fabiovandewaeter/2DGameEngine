#include "Chunk.hpp"

Chunk::Chunk(int positionX, int positionY, int tileSize, std::vector<Texture *> *tileTextures, std::vector<Texture *> *passiveStructureTextures, std::vector<Texture *> *activeStructureTextures, PerlinNoise *perlinNoise)
{
    this->positionX;
    this->positionY;
    this->tileSize = tileSize;
    this->tileTextures = tileTextures;
    this->passiveStructureTextures = passiveStructureTextures;
    this->activeStructureTextures = activeStructureTextures;
    this->box = (SDL_Rect){positionX, positionY, tileSize * SIZE, tileSize * SIZE};
    this->perlinNoise = perlinNoise;
    // loadTiles();
    loadTilesWithPerlinNoise();
    loadPassiveStructures();
    loadActiveStructures();
}
Chunk::~Chunk()
{
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        delete this->allTiles[i];
    }
    for (auto &pair : this->allPassiveStructures)
    {
        delete pair.second;
    }
    for (auto &pair : this->allActiveStructures)
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
            this->allTiles[SIZE * i + j] = new Tile((*this->tileTextures)[0], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize});
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
            this->allTiles[SIZE * i + j] = new Tile((*this->tileTextures)[textureIndex], (SDL_Rect){x, y, this->tileSize, this->tileSize});
        }
    }
}
void Chunk::loadPassiveStructures()
{
    int i = 2, j = 0;
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    this->allPassiveStructures[coordinates] = new Wall((*this->passiveStructureTextures)[0], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize}, true);
    i++;
    i++;
    coordinates = std::to_string(i) + "," + std::to_string(j);
    this->allPassiveStructures[coordinates] = new Wall((*this->passiveStructureTextures)[1], (SDL_Rect){i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize}, true);
    i++;
    i++;
    int x = 2 * this->tileSize, y = 0 * this->tileSize;
}
void Chunk::loadActiveStructures()
{
}

void Chunk::render(Camera *camera)
{
    SDL_Rect renderBox = this->box;
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        for (int i = 0; i < SIZE * SIZE; i++)
        {
            this->allTiles[i]->render(camera);
        }
    }
    for (auto &pair : this->allPassiveStructures)
    {
        pair.second->render(camera);
    }
    for (auto &pair : this->allActiveStructures)
    {
        pair.second->render(camera);
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
Structure *Chunk::getPassiveStructure(int x, int y)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    return this->allPassiveStructures[coordinates];
}
Structure *Chunk::getActiveStructure(int x, int y)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    return this->allActiveStructures[coordinates];
}
bool Chunk::isPassiveStructure(int x, int y)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    if (this->allPassiveStructures.find(coordinates) == this->allPassiveStructures.end())
    {
        return false;
    }
    return true;
}
bool Chunk::isActiveStructure(int x, int y)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    std::string coordinates = std::to_string(i) + "," + std::to_string(j);
    if (this->allActiveStructures.find(coordinates) == this->allActiveStructures.end())
    {
        return false;
    }
    return true;
}
void Chunk::addPassiveStructure(int x, int y, Structure *staticObject)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    if (!isPassiveStructure(i, j))
    {
        SDL_Rect box = {i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize};
        staticObject->setHitBox(box);
        std::string coordinates = std::to_string(i) + "," + std::to_string(j);
        this->allPassiveStructures[coordinates] = staticObject;
    }
}
void Chunk::addActiveStructure(int x, int y, Structure *structure)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    if (!isActiveStructure(i, j))
    {
        SDL_Rect box = {i * this->tileSize + this->box.x, j * this->tileSize + this->box.y, this->tileSize, this->tileSize};
        structure->setHitBox(box);
        std::string coordinates = std::to_string(i) + "," + std::to_string(j);
        this->allActiveStructures[coordinates] = structure;
    }
}
void Chunk::addWall(int x, int y)
{
    addPassiveStructure(x, y, new Wall((*this->passiveStructureTextures)[1], (SDL_Rect){-1, -1, -1, -1}, true));
}
void Chunk::destroyPassiveStructure(int x, int y)
{
    int i = x, j = y;
    convertToTileCoordinates(i, j);
    if (isPassiveStructure(x, y))
    {
        std::string coordinates = std::to_string(i) + "," + std::to_string(j);
        this->allPassiveStructures[coordinates]->destroy();
        this->allPassiveStructures.erase(coordinates);
    }
}