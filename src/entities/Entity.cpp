#include "entities/Entity.hpp"

#include "systems/core/Camera.hpp"
#include "Texture.hpp"
#include "map/Map.hpp"
#include "entities/behaviors/Behavior.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"
#include "entities/states/State.hpp"
#include "entities/actions/Action.hpp"
#include "entities/Faction.hpp"

Entity::~Entity()
{
    delete behavior;
    int size = actionStack.size();
    for (int i = 0; i < size; i++)
    {
        delete actionStack.top();
        actionStack.pop();
    }
    size = inventory.size();
    for (int i = 0; i < size; i++)
    {
        delete inventory[i];
    }
}

void Entity::update()
{
    if (actionStack.empty())
    {
        behavior->update();
    }
    if (!actionStack.empty())
    {
        Action *currentAction = actionStack.top();
        currentAction->update();
        if (currentAction->isCompleted())
        {
            delete currentAction;
            actionStack.pop();
        }
    }
}

void Entity::render(Camera *camera) { camera->render(this); }
void Entity::onCollision(Entity *entity) { std::cout << "Entity#onCollision() does nothing" << std::endl; }
void Entity::onHit(int damage) { HP -= damage; }
void Entity::onLeftClick() { std::cout << "Entity::onLeftClick() does nothing" << std::endl; }
void Entity::onRightClick() { kill(); }
void Entity::attack(Entity *target)
{
    target->onHit(10);
    std::cout << "attack" << std::endl;
}

bool Entity::canMove()
{
    // EXAMPLE: check if it is stunned ...
    return true;
}

bool Entity::isMoving() { return velocityX != 0 || velocityY != 0; }

void Entity::moveBy(float dx, float dy)
{
    // TODO: need change to not call map->handleCollisionsForEntity() 2 times
    if (canMove())
    {
        // check for X axis
        float newPosX = getPositionX() + (VELOCITY_MULTIPLIER * dx);
        SDL_FRect tempRect = map->handleCollisionsForEntity(this, newPosX, getPositionY());
        positionX = tempRect.x;
        // check for Y axis
        float newPosY = getPositionY() + (VELOCITY_MULTIPLIER * dy);
        tempRect = map->handleCollisionsForEntity(this, getPositionX(), newPosY);
        positionY = tempRect.y;
    }
}

void Entity::kill() { HP = 0; }

void Entity::teleportToHome()
{
    std::pair<float, float> homeCoordinates = {0, 0};
    if (faction != nullptr)
    {
        homeCoordinates = faction->getHomeCoordinates();
    }
    positionX = homeCoordinates.first;
    positionY = homeCoordinates.second;
}

// getter
float Entity::getPositionX() const { return positionX; }
float Entity::getPositionY() const { return positionY; }
std::string Entity::getTextureName() const { return textureName; }
SDL_FRect Entity::getHitBox() const { return {positionX, positionY, width, height}; }
float Entity::getSpeed() { return speed; }
int Entity::getHP() { return HP; }
bool Entity::isDead() { return HP <= 0; }
float Entity::getRange() { return range; }
Map *Entity::getMap() const { return map; }
Faction *Entity::getFaction() const { return faction; }

// setter
void Entity::setPosition(float x, float y)
{
    positionX = x;
    positionY = y;
}

void Entity::setVelocity(float velocityX, float velocityY)
{
    this->velocityX = velocityX;
    this->velocityY = velocityY;
}

void Entity::setVelocityX(float velocityX) { this->velocityX = velocityX; }
void Entity::setVelocityY(float velocityY) { this->velocityY = velocityY; }
void Entity::setFaction(Faction *faction) { this->faction = faction; }
void Entity::setBehavior(Behavior *behavior) { this->behavior = behavior; }
void Entity::pushAction(Action *action) { actionStack.push(action); }

void Entity::giveStructure(Structure *structure)
{
    addToInventory(structure);
}

void Entity::addToInventory(Structure *structure)
{
    this->inventory.push_back(structure);
}
