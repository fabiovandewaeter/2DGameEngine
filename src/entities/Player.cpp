#include "entities/Player.hpp"

// 1 if false and sprintVelocity if true
float sprint2 = 1;
float leftVelX2 = 0, rightVelX2 = 0, upVelY2 = 0, downVelY2 = 0;

void Player::handleEvents(SDL_Event *event, MouseManager *mouseManager)
{
    this->camera->handleEvents(event);
    // If a key was pressed
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        // Adjust the velocity
        switch (event->key.keysym.sym)
        {
        case SDLK_i:
            upVelY2 = VELOCITY_MULTIPLIER;
            break;
        case SDLK_k:
            downVelY2 = VELOCITY_MULTIPLIER;
            break;
        case SDLK_j:
            leftVelX2 = VELOCITY_MULTIPLIER;
            break;
        case SDLK_l:
            rightVelX2 = VELOCITY_MULTIPLIER;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            sprint2 = SPRINT_MULTIPLIER;
            break;
        case SDLK_DELETE:
            this->x = 0;
            this->y = 0;
            break;
        }
        this->velX = sprint2 * (rightVelX2 - leftVelX2);
        this->velY = sprint2 * (downVelY2 - upVelY2);
    }
    // If a key was released
    else if (event->type == SDL_KEYUP && event->key.repeat == 0)
    {
        // Adjust the velocity
        switch (event->key.keysym.sym)
        {
        case SDLK_i:
            upVelY2 = 0;
            break;
        case SDLK_k:
            downVelY2 = 0;
            break;
        case SDLK_j:
            leftVelX2 = 0;
            break;
        case SDLK_l:
            rightVelX2 = 0;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            sprint2 = 1;
            break;
        }
        this->velX = sprint2 * (rightVelX2 - leftVelX2);
        this->velY = sprint2 * (downVelY2 - upVelY2);
    }
    if (!this->guiManager->handleEvents(event))
    {
        mouseManager->handleEvents(event, this); // doesnt click on the map if click on GUI
    }
}

void Player::update()
{
    this->camera->update();
    move();
}

void Player::render()
{
    this->camera->renderBackground();
    this->map->render(this);
    this->guiManager->render(this);
}

void Player::move()
{
    // TODO: Player::move() need change to not call map->handleCollisionsForEntity() 2 times
    if (canMove() && isMoving())
    {
        // check for X axis
        float newPosX = this->getPositionX() + (VELOCITY_MULTIPLIER * this->velX);
        SDL_FRect tempRect = this->map->handleCollisionsForEntity(this, newPosX, this->getPositionY());
        this->x = tempRect.x;
        // check for Y axis
        float newPosY = this->getPositionY() + (VELOCITY_MULTIPLIER * this->velY);
        tempRect = this->map->handleCollisionsForEntity(this, this->getPositionX(), newPosY);
        this->y = tempRect.y;
    }
}

Camera *Player::getCamera() { return this->camera; }
