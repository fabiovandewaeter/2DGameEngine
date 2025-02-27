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

void Entity::render(Camera *camera)
{
    camera->render(this);
    /*SDL_FRect renderBox = getHitBox();
    ICI !!!! camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        this->texture->render(renderBox);
    }*/
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
        SDL_FRect tempRect = map->handleCollisionsForEntity(this, newPosX, this->getPositionY());
        this->x = tempRect.x;

        // check for Y axis
        int newPosY = this->getPositionY() + (VELOCITY_MULTIPLIER * dy);
        tempRect = map->handleCollisionsForEntity(this, this->getPositionX(), newPosY);
        this->y = tempRect.y;
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
void Entity::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}
void Entity::setVelocity(float velocityX, float velocityY)
{
    this->velX = velocityX;
    this->velY = velocityY;
}
void Entity::setVelocityX(float velocityX) { this->velX = velocityX; }
void Entity::setVelocityY(float velocityY) { this->velY = velocityY; }
void Entity::setFaction(Faction *faction) { this->faction = faction; }
void Entity::pushAction(Action *action) { this->actionStack.push(action); }

// getter
float Entity::getPositionX() { return this->x; }
float Entity::getPositionY() { return this->y; }
// int Entity::getCenterX() { return this->hitBox.w / 2; }
// int Entity::getCenterY() { return this->hitBox.h / 2; }
Texture *Entity::getTexture() const { return this->texture; }
SDL_FRect Entity::getHitBox() const { return {this->x, this->y, this->width, this->height}; }
int Entity::getHP() { return this->HP; }
Map *Entity::getMap() const { return this->map; }
int Entity::getSpeed() { return this->speed; }
