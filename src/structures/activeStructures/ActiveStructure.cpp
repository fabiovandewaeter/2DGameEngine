#include "ActiveStructure.hpp"

#include "../../map/Map.hpp"

ActiveStructure::ActiveStructure() {}
ActiveStructure::~ActiveStructure() {}

void ActiveStructure::init(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, Map *map, SDL_Rect hitBox, unsigned int HP)
{
    Structure::init(texture, collisionManager, hitBox, 1, HP, true);
    this->collisionManager = collisionManager;
    this->entityManager = entityManager;
    this->map = map;
}

void ActiveStructure::spawnEntities() {}
std::vector<SDL_Rect> ActiveStructure::getPotentialSpawnTiles()
{
    int tileSize = this->map->getTileSize();
    std::vector<SDL_Rect> potentialSpawnTiles;

    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - 1, this->hitBox.y - 1, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x, this->hitBox.y - 1, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize + 1, this->hitBox.y - 1, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize + 1, this->hitBox.y, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x + tileSize + 1, this->hitBox.y + tileSize + 1, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x, this->hitBox.y + tileSize + 1, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - 1, this->hitBox.y + tileSize + 1, this->hitBox.w, this->hitBox.h});
    potentialSpawnTiles.push_back((SDL_Rect){this->hitBox.x - 1, this->hitBox.y, this->hitBox.w, this->hitBox.h});

    return potentialSpawnTiles;
}