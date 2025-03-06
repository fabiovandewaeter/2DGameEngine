#include "systems/game_objects/EntityManager.hpp"

#include <cmath>
#include <limits>

#include "systems/core/Camera.hpp"
#include "systems/core/TextureManager.hpp"
#include "Texture.hpp"
#include "entities/Entity.hpp"
#include "entities/Faction.hpp"

void EntityManager::loadEntities()
{
    // this->entities.push_back(new Entity((*this->entityTextures)[1], (SDL_FRect){50, 50, 16, 16}, 100));
}

void EntityManager::update()
{
    int size = this->entities.size();
    std::vector<int> deadEntities;

    // update entities
    for (int i = 0; i < size; i++)
    {
        this->entities[i]->update();
        if (this->entities[i]->getHP() <= 0)
        {
            deadEntities.push_back(i);
        }
    }

    // delete dead entities
    for (int i = deadEntities.size() - 1; i >= 0; i--)
    {
        int index = deadEntities[i];
        Entity *tempo = this->entities[index];
        this->entities.erase(this->entities.begin() + index);
        delete tempo;
    }
}

void EntityManager::render(Camera *camera)
{
    int size = this->entities.size();
    for (int i = 0; i < size; i++)
    {
        entities[i]->render(camera);
    }
}

void EntityManager::addPlayer(Player *player)
{
    this->players.push_back(player);
    addEntity((Entity *)player);
}

void EntityManager::addEntity(Entity *entity)
{
    this->entities.push_back(entity);
    std::cout << this->entities.size() << std::endl;
}

bool EntityManager::checkCollision(SDL_FRect rectA, SDL_FRect rectB)
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
    // TODO: NEED CHANGE IN EntityManager::getPotentialEntities() TO ONLY RETURN THE POTENTIAL ENTITIES AND NOT ALL ENTITIES
    return this->entities;
}

std::vector<Entity *> EntityManager::getEntitiesInArea(SDL_FRect area)
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

std::vector<Player *> *EntityManager::getPlayers() { return &this->players; }
int EntityManager::getNumberOfPlayers() { return this->players.size(); }

Entity *EntityManager::findClosestEnemy(const Entity *entity)
{
    Entity *closestEnemy = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    Faction *entityFaction = entity->getFaction();

    for (Entity *other : entities)
    {
        // Ne pas se considérer soi-même comme ennemi
        if (other == entity)
            continue;

        // Vérifier l'appartenance aux factions
        Faction *otherFaction = other->getFaction();

        if (entityFaction && otherFaction)
        {
            // Si les factions sont alliées, on skip
            if (entityFaction->isAlliedWith(otherFaction))
                continue;
        }
        else if (!entityFaction || !otherFaction)
        {
            float dx = other->getPositionX() - entity->getPositionX();
            float dy = other->getPositionY() - entity->getPositionY();
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < minDistance)
            {
                minDistance = distance;
                closestEnemy = other;
            }
        }
    }
    return closestEnemy;
}
