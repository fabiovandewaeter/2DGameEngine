#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "map/Chunk.hpp"

#include "map/Tile.hpp"
#include "systems/algorithms/PerlinNoise.hpp"
#include "systems/core/Camera.hpp"
#include "systems/game_objects/ItemFactory.hpp"
#include "systems/core/TextureManager.hpp"
#include "structures/passiveStructures/Wall.hpp"
#include "structures/IUpdatable.hpp"
#include "systems/utils/Constants.hpp"

Chunk::Chunk(int positionX, int positionY, Map *map, TextureManager *textureManager, PerlinNoise *perlinNoise, CollisionManager *collisionManager)
{
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = TILE_SIZE * CHUNK_SIZE;
    this->height = TILE_SIZE * CHUNK_SIZE;
    this->map = map;
    this->textureManager = textureManager;
    this->perlinNoise = perlinNoise;
    loadTiles();
    loadUpdatableStructures();
    loadOtherStructures();
}
Chunk::~Chunk()
{
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
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
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            this->allTiles[CHUNK_SIZE * i + j] = new Tile(this->textureManager->getTexture("grass_0"), i + this->positionX, j + this->positionY);
        }
    }
}
void Chunk::loadTilesWithPerlinNoise()
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            float x = i + this->positionX;
            float y = j + this->positionY;
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
            this->allTiles[CHUNK_SIZE * i + j] = new Tile(this->textureManager->getTexture(textureName), x, y);
        }
    }
}
void Chunk::loadUpdatableStructures() {}
void Chunk::loadOtherStructures() {}

void Chunk::render(Camera *camera)
{
    SDL_FRect renderBox = {this->positionX, this->positionY, this->width, this->height};
    SDL_Rect newRenderBox = camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisibleOnScreen(newRenderBox))
    {
        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
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

std::pair<int, int> Chunk::convertToLocalTileCoordinates(float x, float y)
{
    x = static_cast<int>(std::floor(x)) % CHUNK_SIZE;
    y = static_cast<int>(std::floor(y)) % CHUNK_SIZE;
    if (x < 0)
    {
        x = CHUNK_SIZE + x;
    }
    if (y < 0)
    {
        y = CHUNK_SIZE + y;
    }
    std::pair<int, int> res = {x, y};
    return res;
}

// returns the tile that contains the coordinates
Tile *Chunk::getTile(float x, float y)
{
    std::pair<int, int> newCoordinates = convertToLocalTileCoordinates(x, y);
    return this->allTiles[CHUNK_SIZE * newCoordinates.first + newCoordinates.second];
}
Structure *Chunk::getStructure(float x, float y)
{
    std::pair<int, int> newCoordinates = convertToLocalTileCoordinates(x, y);
    auto it = this->updatableStructures.find(newCoordinates);
    if (it != this->updatableStructures.end())
    {
        return it->second;
    }
    else
    {
        it = this->otherStructures.find(newCoordinates);
        if (it != this->otherStructures.end())
        {
            return it->second;
        }
    }
    return nullptr;
}

bool Chunk::isStructure(float x, float y)
{
    std::pair<int, int> newCoordinates = convertToLocalTileCoordinates(x, y);

    auto it = this->updatableStructures.find(newCoordinates);
    if (it != this->updatableStructures.end())
    {
        return true;
    }
    else
    {
        it = this->otherStructures.find(newCoordinates);
        if (it != this->otherStructures.end())
        {
            return true;
        }
    }
    return false;
}

void Chunk::addStructure(Structure *structure)
{
    SDL_FRect hitBox = structure->getHitBox();
    float x = hitBox.x;
    float y = hitBox.y;
    if (!isStructure(x, y))
    {
        std::pair<int, int> newCoordinates = convertToLocalTileCoordinates(x, y);
        SDL_FRect box = {newCoordinates.first + this->positionX, newCoordinates.second + this->positionY, 1, 1};
        structure->setHitBox(box);

        if (IUpdatable *updatable = dynamic_cast<IUpdatable *>(structure))
        {
            this->updatableStructures[newCoordinates] = structure;
        }
        else
        {
            this->otherStructures[newCoordinates] = structure;
        }
    }
}

void Chunk::destroyStructure(float x, float y)
{
    if (isStructure(x, y))
    {
        std::pair<int, int> newCoordinates = convertToLocalTileCoordinates(x, y);

        Structure *structure = getStructure(newCoordinates.first, newCoordinates.second);
        if (IUpdatable *updatable = dynamic_cast<IUpdatable *>(structure))
        {
            this->updatableStructures.erase(newCoordinates);
        }
        else
        {
            this->otherStructures.erase(newCoordinates);
        }
        structure->destroy();
    }
}
void Chunk::setFaction(Faction *faction) { this->faction = faction; }
