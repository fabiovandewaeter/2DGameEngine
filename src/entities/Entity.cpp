#include "entities/Entity.hpp"

#include "systems/core/Camera.hpp"
#include "Texture.hpp"
#include "entities/states/State.hpp"
#include "map/Map.hpp"
#include "entities/behaviors/Behavior.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"
#include "entities/actions/Action.hpp"

void Entity::update()
{
    std::cout << "Entity: " << this->HP - 100 << std::endl;
    if (this->actionStack.empty())
    {
        this->behavior->execute(this);
    }
    if (!this->actionStack.empty())
    {
        Action *currentAction = actionStack.top();
        currentAction->execute(this);
        if (currentAction->isCompleted())
        {
            delete currentAction;
            actionStack.pop();
        }
    }
}

/*void Entity::move()
{
    if (canMove() && isMoving())
    {
        std::cout << "Entity::move() need change to not call map->handleCollisionsForEntity() 2 times" << std::endl;
        // check for X axis
        int newPosX = this->getPositionX() + (VELOCITY_MULTIPLIER * this->velX);
        map->handleCollisionsForEntity(this, newPosX, this->getPositionY());
        SDL_Rect tempRect = this->map->handleCollisionsForEntity(this, newPosX, this->getPositionY());
        this->hitBox.x = tempRect.x;

        // check for Y axis
        int newPosY = this->getPositionY() + (VELOCITY_MULTIPLIER * this->velY);
        tempRect = this->map->handleCollisionsForEntity(this, this->getPositionX(), newPosY);
        this->hitBox.y = tempRect.y;
    }
}*/

void Entity::render(Camera *camera)
{
    SDL_Rect renderBox = this->hitBox;
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        this->texture->render(renderBox);
    }
}
void Entity::onCollision(Entity *entity)
{
    std::cout << "Entity#onCollision() does nothing" << std::endl;
}
void Entity::hit(int damage)
{
    this->HP -= damage;
}
void Entity::onLeftClick() { std::cout << "Entity::onLeftClick() does nothing" << std::endl; }
void Entity::onRightClick() { kill(); }
void Entity::moveBy(float dx, float dy)
{
    if (canMove() && isMoving())
    {
        std::cout << "Entity::move() need change to not call map->handleCollisionsForEntity() 2 times" << std::endl;
        // check for X axis
        int newPosX = this->getPositionX() + (VELOCITY_MULTIPLIER * dx);
        map->handleCollisionsForEntity(this, newPosX, this->getPositionY());
        SDL_Rect tempRect = map->handleCollisionsForEntity(this, newPosX, this->getPositionY());
        this->hitBox.x = tempRect.x;

        // check for Y axis
        int newPosY = this->getPositionY() + (VELOCITY_MULTIPLIER * dy);
        tempRect = map->handleCollisionsForEntity(this, this->getPositionX(), newPosY);
        this->hitBox.y = tempRect.y;
    }
}
void Entity::kill() { this->HP = 0; }

bool Entity::canMove()
{
    // EXAMPLE: check if it is stunned ...
    return true;
}
bool Entity::isMoving()
{
    return this->velX != 0 || this->velY != 0;
}

// setter
void Entity::setPosition(int x, int y)
{
    this->hitBox.x = x;
    this->hitBox.y = y;
}
void Entity::setVelocity(int velocityX, int velocityY)
{
    this->velX = velocityX;
    this->velY = velocityY;
}
void Entity::setVelocityX(int velocityX) { this->velX = velocityX; }
void Entity::setVelocityY(int velocityY) { this->velY = velocityY; }
void Entity::setFaction(Faction *faction) { this->faction = faction; }

// getter
int Entity::getPositionX() { return this->hitBox.x; }
int Entity::getPositionY() { return this->hitBox.y; }
int Entity::getCenterX() { return this->hitBox.w / 2; }
int Entity::getCenterY() { return this->hitBox.h / 2; }
SDL_Rect Entity::getHitBox() { return this->hitBox; }
int Entity::getHP() { return this->HP; }
Map *Entity::getMap() { return this->map; }
int Entity::getSpeed() { return this->speed; }
