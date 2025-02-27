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
    this->map = map;
    this->textureManager = textureManager;
    this->box = (SDL_FRect){positionX, positionY, TILE_SIZE * CHUNK_SIZE, TILE_SIZE * CHUNK_SIZE};
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
            this->allTiles[CHUNK_SIZE * i + j] = new Tile(this->textureManager->getTexture("grass_0"), i + this->box.x, j + this->box.y);
        }
    }
}
void Chunk::loadTilesWithPerlinNoise()
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            float x = i + this->box.x;
            float y = j + this->box.y;
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
    SDL_FRect renderBox = this->box;
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

void Chunk::convertToTileCoordinates(int &x, int &y)
{
    x = static_cast<int>(std::floor(static_cast<float>(x) / TILE_SIZE)) % CHUNK_SIZE;
    y = static_cast<int>(std::floor(static_cast<float>(y) / TILE_SIZE)) % CHUNK_SIZE;
    if (x < 0)
    {
        x = CHUNK_SIZE + x;
    }
    if (y < 0)
    {
        y = CHUNK_SIZE + y;
    }
}
// returns the tile that contains the coordinates
Tile *Chunk::getTile(int x, int y)
{
    convertToTileCoordinates(x, y);
    return this->allTiles[CHUNK_SIZE * x + y];
}
Structure *Chunk::getStructure(int x, int y)
{
#ifdef PROFILER
    ZoneScoped;
#endif
    convertToTileCoordinates(x, y);
    // std::string coordinates = std::to_string(x) + "," + std::to_string(y);
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
    convertToTileCoordinates(x, y);
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
    SDL_FRect hitBox = structure->getHitBox();
    int x = hitBox.x;
    int y = hitBox.y;
    if (!isStructure(x, y))
    {
        convertToTileCoordinates(x, y);
        SDL_FRect box = {x * TILE_SIZE + this->box.x, y * TILE_SIZE + this->box.y, TILE_SIZE, TILE_SIZE};
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
        convertToTileCoordinates(x, y);
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
