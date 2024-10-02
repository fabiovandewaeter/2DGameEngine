#include "EntityManager.hpp"

#include "Camera.hpp"
#include "CollisionManager.hpp"
#include "../Texture.hpp"
#include "../entities/Entity.hpp"
#include "../entities/Entity.hpp"

EntityManager::EntityManager() {}
EntityManager::~EntityManager() {}

void EntityManager::init(Camera *camera, CollisionManager *collisionManager, std::vector<Texture *> *entityTextures)
{
    this->collisionManager = collisionManager;
    this->entityTextures = entityTextures;
    this->camera = camera;
}

void EntityManager::loadEntities()
{
    this->entities.push_back(new Entity((*this->entityTextures)[1], (SDL_Rect){50, 50, 16, 16}));
}
void EntityManager::update()
{
    int size = this->entities.size();
    for (int i = 0; i < size; i++)
    {
        this->entities[i]->update(this->collisionManager);
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

void EntityManager::addEntity(Entity *entity)
{
    this->entities.push_back(entity);
    std::cout << this->entities.size() << std::endl;
}
std::vector<Entity *> EntityManager::getPotentialEntities(Entity *entity)
{
    return this->entities;
}
Entity *EntityManager::generateDefaultEntity(SDL_Rect hitBox)
{
    return new Entity((*this->entityTextures)[0], hitBox);
}