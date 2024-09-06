#include "Entity.hpp"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::init(Texture *texture, SDL_Rect hitBox)
{
    this->texture = texture;
    this->hitBox = hitBox;
    this->velX = 0;
    this->velY = 0;
    this->velocity= 1;
}

bool Entity::update()
{
    return move();
}

bool Entity::move()
{
    bool success = true;

    // EXAMPLE: check if he stunned ...
    this->hitBox.x += this->velocity* this->velX;
    this->hitBox.y += this->velocity * this->velY;

    return success;
}

void Entity::render(SDL_Renderer *renderer, int cameraCenterX, int cameraCenterY, int cameraPositionX, int cameraPositionY, double scale)
{
    this->texture->render(renderer, (cameraCenterX-cameraPositionX*scale) - ((this->getCenterX()+this->hitBox.x) * scale), (cameraCenterY-cameraPositionY*scale) - ((this->getCenterY()+this->hitBox.y) * scale), this->hitBox.w, this->hitBox.h, scale);
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
int Entity::getCenterX(){
    return this->hitBox.w/2;
}
int Entity::getCenterY(){
    return this->hitBox.h/2;
}
Texture *Entity::getTexture()
{
    return this->texture;
}