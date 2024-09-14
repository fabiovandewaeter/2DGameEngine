#include "Entity.hpp"

Entity::Entity() {}
Entity::Entity(Texture *texture, SDL_Rect hitBox, bool solid)
{
    init(texture, hitBox, solid);
}
Entity::~Entity() {}

void Entity::init(Texture *texture, SDL_Rect hitBox, bool solid)
{
    this->texture = texture;
    this->hitBox = hitBox;
    this->velX = 0;
    this->velY = 0;
    this->solid = solid;
}

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
        int newPosX = this->getPositionX() + (VELOCITY_MULTIPLIER * this->velX);
        int newPosY = this->getPositionY() + (VELOCITY_MULTIPLIER * this->velY);

        SDL_Rect newRect = collisionManager->handleCollisionsFor(this, newPosX, newPosY);

        this->hitBox.x = newRect.x;
        this->hitBox.y = newRect.y;
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

void Entity::setVelocity(int velocityX, int velocityY)
{
    this->velX = velocityX;
    this->velY = velocityY;
}
void Entity::setVelocityX(int velocityX)
{
    this->velX = velocityX;
}
void Entity::setVelocityY(int velocityY)
{
    this->velY = velocityY;
}
int Entity::getPositionX()
{
    return this->hitBox.x;
}
int Entity::getPositionY()
{
    return this->hitBox.y;
}
int Entity::getCenterX()
{
    return this->hitBox.w / 2;
}
int Entity::getCenterY()
{
    return this->hitBox.h / 2;
}
SDL_Rect Entity::getHitBox()
{
    return this->hitBox;
}
bool Entity::isSolid()
{
    return this->solid;
}