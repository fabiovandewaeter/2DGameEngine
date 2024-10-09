#include "ActiveStructure.hpp"

#include "../../map/Map.hpp"

ActiveStructure::ActiveStructure(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP, bool solid) : Structure(texture, hitBox, HP, solid)
{
    this->collisionManager = collisionManager;
    this->entityManager = entityManager;
    this->map = map;
    this->active = true;
}
ActiveStructure::~ActiveStructure() {}

void ActiveStructure::spawnEntities() {}
std::vector<SDL_Rect> ActiveStructure::getPotentialSpawnTiles()
{
    int tileSize = this->map->getTileSize();
    std::vector<SDL_Rect> potentialSpawnTiles;

    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - tileSize, this->hitBox.y - tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x, this->hitBox.y - tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize, this->hitBox.y - tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize, this->hitBox.y, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize, this->hitBox.y + tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x, this->hitBox.y + tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - tileSize, this->hitBox.y + tileSize, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - tileSize, this->hitBox.y, this->hitBox.w, this->hitBox.h});

    return potentialSpawnTiles;
}