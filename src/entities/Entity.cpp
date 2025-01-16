#include "entities/Entity.hpp"

#include "systems/CollisionManager.hpp"
#include "systems/core/Camera.hpp"
#include "Texture.hpp"
#include "entities/states/State.hpp"

Entity::Entity(Texture *texture, SDL_Rect hitBox, int HP)
{
    this->texture = texture;
    this->hitBox = hitBox;
    this->HP = HP;
    this->velX = 0;
    this->velY = 0;
    this->state = nullptr;
}
Entity::~Entity() {}

void Entity::update(CollisionManager *collisionManager)
{
    move(collisionManager);
}

bool Entity::canMove()
{
    // EXAMPLE: check if it is stunned ...
    return true;
}
bool Entity::isMoving()
{
    return this->velX != 0 || this->velY != 0;
}

void Entity::move(CollisionManager *collisionManager)
{
    if (canMove() && isMoving())
    {
        // check for X axis
        int newPosX = this->getPositionX() + (VELOCITY_MULTIPLIER * this->velX);
        SDL_Rect tempRect = collisionManager->handleCollisionsFor(this, newPosX, this->getPositionY());
        this->hitBox.x = tempRect.x;

        // check for Y axis
        int newPosY = this->getPositionY() + (VELOCITY_MULTIPLIER * this->velY);
        tempRect = collisionManager->handleCollisionsFor(this, this->getPositionX(), newPosY);
        this->hitBox.y = tempRect.y;
    }
}


void Entity::render(Camera *camera)
{
    SDL_Rect renderBox = this->hitBox;
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        this->texture->render(renderBox);
    }
}
void Entity::kill(){
    
    this->HP = 0;
    this->state = nullptr;
}
void Entity::onCollision(Entity *entity)
{
    std::cout << "Entity#onCollision()" << std::endl;
}
void Entity::hit(int damage)
{
    this->HP -= damage;
}
void Entity::onLeftClick() { std::cout << "fait rien RIGHT" << std::endl; }
void Entity::onRightClick() { kill(); }

void Entity::setVelocity(int velocityX, int velocityY)
{
    this->velX = velocityX;
    this->velY = velocityY;
}
void Entity::setVelocityX(int velocityX) { this->velX = velocityX; }
void Entity::setVelocityY(int velocityY) { this->velY = velocityY; }
void Entity::setFaction(Faction *faction) { this->faction = faction; }

int Entity::getPositionX() { return this->hitBox.x; }
int Entity::getPositionY() { return this->hitBox.y; }
int Entity::getCenterX() { return this->hitBox.w / 2; }
int Entity::getCenterY() { return this->hitBox.h / 2; }
SDL_Rect Entity::getHitBox() { return this->hitBox; }
int Entity::getHP() { return this->HP; }