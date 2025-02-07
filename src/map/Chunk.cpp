#include "map/Chunk.hpp"

#include "map/Tile.hpp"
#include "systems/PerlinNoise.hpp"
#include "systems/core/Camera.hpp"
#include "systems/game_objects/ItemFactory.hpp"
#include "systems/core/TextureManager.hpp"
#include "structures/passiveStructures/Wall.hpp"
#include "structures/IUpdatable.hpp"

#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif
Chunk::Chunk(int positionX, int positionY, int tileSize, Map *map, TextureManager *textureManager, PerlinNoise *perlinNoise, CollisionManager *collisionManager)
{
    this->positionX = positionX;
    this->positionY = positionY;
    this->tileSize = tileSize;
    this->map = map;
    this->textureManager = textureManager;
    this->box = (SDL_Rect){positionX, positionY, tileSize * SIZE, tileSize * SIZE};
    this->perlinNoise = perlinNoise;
    loadTiles();
    loadPassiveStructures();
    loadActiveStructures();
}
Chunk::~Chunk()
{
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        delete this->allTiles[i];
    }
    for (auto &pair : this->updatableStructures)
    {
        delete pair.second;
    }
    for (auto &pair : this->otherStructures)
    {
        delete pair.second;
    }
}

void Chunk::loadTiles()
{
    loadTilesWithPerlinNoise();
}
void Chunk::loadTilesDefault()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            this->allTiles[SIZE * i + j] = new Tile(this->textureManager->getTexture("grass_0"), i * this->tileSize + this->box.x, j * this->tileSize + this->box.y);
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
            std::string textureName = "grass_" + std::to_string(textureIndex);
            this->allTiles[SIZE * i + j] = new Tile(this->textureManager->getTexture(textureName), x, y);
        }
    }
}
void Chunk::loadPassiveStructures() {}
void Chunk::loadActiveStructures() {}

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
    for (auto &pair : this->updatableStructures)
    {
        pair.second->render(camera);
    }
    for (auto &pair : this->otherStructures)
    {
        pair.second->render(camera);
    }
}

void Chunk::update()
{
    std::vector<std::pair<int, int>> updatableStructuresToRemove;
    std::vector<std::pair<int, int>> otherStructuresToRemove;
    for (auto &[coords, structure] : this->updatableStructures)
    {
        structure->update();
        if (structure->isDestroyed())
        {
            updatableStructuresToRemove.push_back(coords);
        }
    }
    // NEED CHANGE TO NOT CHECK EVERY TICK IF ALL WALLS ARE DESTROYED
    for (auto &[coords, structure] : this->otherStructures)
    {
        if (structure->isDestroyed())
        {
            otherStructuresToRemove.push_back(coords);
        }
    }
    for (const auto &coords : updatableStructuresToRemove)
    {
        delete this->updatableStructures[coords];
        this->updatableStructures.erase(coords);
    }
    for (const auto &coords : otherStructuresToRemove)
    {
        delete this->otherStructures[coords];
        this->otherStructures.erase(coords);
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
    //convertToTileCoordinates(x, y);
    return this->allTiles[SIZE * x + y];
}
Structure *Chunk::getStructure(int x, int y)
{
#ifdef PROFILER
    ZoneScoped;
#endif
    convertToTileCoordinates(x, y);
    //std::string coordinates = std::to_string(x) + "," + std::to_string(y);
    std::pair<int, int> coordinates = {x, y};

    auto it = this->updatableStructures.find(coordinates);
    if (it != this->updatableStructures.end())
    {
        return it->second;
    }
    else
    {

        it = this->otherStructures.find(coordinates);
        if (it != this->otherStructures.end())
        {
            return it->second;
        }
    }
    return nullptr;
}

bool Chunk::isStructure(int x, int y)
{
    //convertToTileCoordinates(x, y);
    std::pair<int, int> coordinates = {x, y};

    auto it = this->updatableStructures.find(coordinates);
    if (it != this->updatableStructures.end())
    {
        return true;
    }
    else
    {

        it = this->otherStructures.find(coordinates);
        if (it != this->otherStructures.end())
        {
            return true;
        }
    }
    return false;
}

void Chunk::addStructure(Structure *structure)
{
    SDL_Rect hitBox = structure->getHitBox();
    int x = hitBox.x;
    int y = hitBox.y;
    if (!isStructure(x, y))
    {
        //convertToTileCoordinates(x, y);
        SDL_Rect box = {x * this->tileSize + this->box.x, y * this->tileSize + this->box.y, this->tileSize, this->tileSize};
        structure->setHitBox(box);
        std::pair<int, int> coordinates = {x, y};

        if (IUpdatable *updatable = dynamic_cast<IUpdatable *>(structure))
        {
            this->updatableStructures[coordinates] = structure;
        }
        else
        {
            this->otherStructures[coordinates] = structure;
        }
    }
}

void Chunk::destroyStructure(int x, int y)
{
    if (isStructure(x, y))
    {
        //convertToTileCoordinates(x, y);
        std::pair<int, int> coordinates = {x, y};

        Structure *structure = getStructure(x, y);
        if (IUpdatable *updatable = dynamic_cast<IUpdatable *>(structure))
        {
            this->updatableStructures.erase(coordinates);
        }
        else
        {
            this->otherStructures.erase(coordinates);
        }
        structure->destroy();
    }
}
void Chunk::setFaction(Faction *faction) { this->faction = faction; }
