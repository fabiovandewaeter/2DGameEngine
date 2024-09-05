#include "Entity.hpp"


Entity::Entity() {}
Entity::~Entity() {}

void Entity::init(LTexture *texture, SDL_Rect position)
{
    this->texture = texture;
    this->position = position;
    this->velX = 0;
    this->velY = 0;
    this->VELOCITY = 1;
    this->SPRINT_VELOCITY = 2;
    // 1 if false and SPRINT_VELOCITY if true
    this->sprint = 1;
    this->leftVelX = 0;
    this->rightVelX = 0;
    this->upVelY = 0;
    this->downVelY = 0;
}

bool Entity::update()
{
    return move();
}


void Entity::handleEvents(SDL_Event *event)
{
    // If a key was pressed
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        // Adjust the velocity
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_z:
            upVelY = VELOCITY;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            downVelY = VELOCITY;
            break;
        case SDLK_LEFT:
        case SDLK_q:
            leftVelX = VELOCITY;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            rightVelX = VELOCITY;
            break;
        case SDLK_LSHIFT:
            sprint = SPRINT_VELOCITY;
            break;
        }
        this->velX = sprint*(rightVelX - leftVelX);
        this->velY = sprint*(downVelY - upVelY);
    }
    // If a key was released
    else if (event->type == SDL_KEYUP && event->key.repeat == 0)
    {
        // Adjust the velocity
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_z:
            upVelY = 0;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            downVelY = 0;
            break;
        case SDLK_LEFT:
        case SDLK_q:
            leftVelX = 0;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            rightVelX = 0;
            break;
        case SDLK_LSHIFT:
            sprint = 1;
            break;
        }
        this->velX = sprint*(rightVelX - leftVelX);
        this->velY = sprint*(downVelY - upVelY);
    }
}

bool Entity::move()
{
    bool success = true;

    // EXAMPLE: check if he stunned ...
    position.x += VELOCITY*velX;
    position.y += VELOCITY*velY;

    return success;
}

void Entity::render(SDL_Renderer *renderer)
{
    texture->render(position.x, position.y, renderer);
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