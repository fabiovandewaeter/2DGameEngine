#include "systems/game_objects/EntityManager.hpp"

#include "systems/core/Camera.hpp"
#include "systems/core/TextureManager.hpp"
#include "systems/CollisionManager.hpp"
#include "Texture.hpp"
#include "entities/Entity.hpp"
#include "entities/Entity.hpp"

EntityManager::EntityManager() {}
EntityManager::~EntityManager() {}

void EntityManager::init(Camera *camera, CollisionManager *collisionManager, TextureManager *textureManager)
{
    this->collisionManager = collisionManager;
    this->entityTextures = entityTextures;
    this->camera = camera;
}

void EntityManager::loadEntities()
{
    //this->entities.push_back(new Entity((*this->entityTextures)[1], (SDL_Rect){50, 50, 16, 16}, 100));
}

void EntityManager::update() {
    int size = this->entities.size();
    std::vector<int> deadEntities;

    // update entities
    for (int i = 0; i < size; i++) {
        this->entities[i]->update(this->collisionManager);
        if (this->entities[i]->getHP() <= 0) {
            deadEntities.push_back(i);
        }
    }

    // delete dead entities
    for (int i = deadEntities.size() - 1; i >= 0; i--) {
        int index = deadEntities[i];
        Entity* tempo = this->entities[index];
        this->entities.erase(this->entities.begin() + index);
        delete tempo;
    }
}

void EntityManager::render()
{
    int size = this->entities.size();
    for (int i = 0; i < size; i++)
    {
        entities[i]->render(this->camera);
    }
}

void EntityManager::addPlayer(Player *player)
{
    this->player = player;
    addEntity((Entity *)player);
}
void EntityManager::addEntity(Entity *entity)
{
    this->entities.push_back(entity);
    std::cout << this->entities.size() << std::endl;
}
bool EntityManager::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    return !(rectA.x + rectA.w <= rectB.x ||
             rectA.x >= rectB.x + rectB.w ||
             rectA.y + rectA.h <= rectB.y ||
             rectA.y >= rectB.y + rectB.h);
}
std::vector<Entity *> EntityManager::getEntities()
{
    return this->entities;
}
std::vector<Entity *> EntityManager::getPotentialEntities(Entity *entity)
{
    // NEED CHANGE
    std::cout << "NEED CHANGE IN EntityManager::getPotentialEntities()" << std::endl;
    return this->entities;
}
std::vector<Entity *> EntityManager::getEntitiesInArea(SDL_Rect area)
{
    std::vector<Entity *> res;
    int size = this->entities.size();
    for (int i = 0; i < size; i++)
    {
        if (checkCollision(this->entities[i]->getHitBox(), area))
        {
            res.push_back(this->entities[i]);
        }
    }
    return res;
}
Entity *EntityManager::generateDefaultEntity(SDL_Rect hitBox)
{
    return new Entity((*this->entityTextures)[0], hitBox, 100);
}
Player *EntityManager::getPlayer() { return this->player; }
