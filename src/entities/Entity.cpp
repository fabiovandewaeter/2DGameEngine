#include "Entity.hpp"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::init(Texture *texture, SDL_Rect hitBox, bool solid)
{
    this->texture = texture;
    this->hitBox = hitBox;
    this->velX = 0;
    this->velY = 0;
    this->velocity = 1;
    this->solid = solid;
}

void Entity::update(CollisionManager *collisionManager)
{
    move(collisionManager);
}

bool Entity::canMove()
{
    // EXAMPLE: check if he is stunned ...
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
        int newPosX = this->getPositionX() + (this->velocity * this->velX);
        int newPosY = this->getPositionY() + (this->velocity * this->velY);

        SDL_Rect newRect = collisionManager->handleCollisionsFor(this, newPosX, newPosY);

        this->hitBox.x = newRect.x;
        this->hitBox.y = newRect.y;
    }
}

void Entity::render(SDL_Renderer *renderer, int viewCenterX, int viewCenterY, int cameraPositionX, int cameraPositionY, double scale, Camera *camera)
{
    int viewPositionX = (viewCenterX - cameraPositionX * scale) - ((this->getCenterX() + this->hitBox.x) * scale);
    int viewPositionY = (viewCenterY - cameraPositionY * scale) - ((this->getCenterY() + this->hitBox.y) * scale);
    if (camera->isVisible(this->hitBox, viewPositionX, viewPositionY))
    {
        this->texture->render(renderer, viewPositionX, viewPositionY, this->hitBox.w, this->hitBox.h, scale);
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
Texture *Entity::getTexture()
{
    return this->texture;
}
SDL_Rect Entity::getHitBox()
{
    return this->hitBox;
}
bool Entity::isSolid()
{
    return this->solid;
}