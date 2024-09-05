#include "Entity.hpp"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::init(LTexture *texture, int positionX, int positionY)
{
    this->texture = texture;
    this->positionX = positionX;
    this->positionY = positionY;
    this->velX = 0;
    this->velY = 0;
    this->VELOCITY = 1;
}

bool Entity::update()
{
    return move();
}

bool Entity::move()
{
    bool success = true;

    // EXAMPLE: check if he stunned ...
    positionX += VELOCITY * velX;
    positionY += VELOCITY * velY;

    return success;
}

void Entity::render(SDL_Renderer *renderer, int cameraX, int cameraY, double scale)
{
    //texture->render(renderer, (positionX - cameraX)*scale, (positionY - cameraY)*scale, scale);
    texture->render(renderer, (positionX - cameraX)*scale, (positionY - cameraY)*scale, scale);
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
    return this->positionX;
}
int Entity::getPositionY()
{
    return this->positionY;
}
LTexture *Entity::getTexture()
{
    return this->texture;
}