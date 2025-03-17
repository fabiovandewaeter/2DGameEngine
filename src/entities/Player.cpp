#include "entities/Player.hpp"

// 1 if false and sprintVelocity if true
float sprint2 = 1;
float leftVelX2 = 0, rightVelX2 = 0, upVelY2 = 0, downVelY2 = 0;

Player::~Player()
{
    delete camera;
    delete mouseManager;
    delete guiManager;
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

void Player::handleEvents(SDL_Event *event)
{
    camera->handleEvents(event);
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
            positionX = 0;
            positionY = 0;
            break;
        }
        velocityX = sprint2 * (rightVelX2 - leftVelX2);
        velocityY = sprint2 * (downVelY2 - upVelY2);
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
        velocityX = sprint2 * (rightVelX2 - leftVelX2);
        velocityY = sprint2 * (downVelY2 - upVelY2);
    }
    if (!guiManager->handleEvents(event))
    {
        mouseManager->handleEvents(event, this); // doesnt click on the map if click on GUI
    }
}

void Player::update()
{
    camera->update();
    move();
}

void Player::render()
{
    if (camera->isActive())
    {
        SDL_RenderClear(camera->getRenderer());
        camera->renderBackground();
        map->render(camera);
        guiManager->render(this);
        SDL_RenderPresent(camera->getRenderer());
    }
}

void Player::move()
{
    // TODO: Player::move() need change to not call map->handleCollisionsForEntity() 2 times
    if (canMove() && isMoving())
    {
        // check for X axis
        float newPosX = getPositionX() + (VELOCITY_MULTIPLIER * velocityX);
        SDL_FRect tempRect = map->handleCollisionsForEntity(this, newPosX, getPositionY());
        positionX = tempRect.x;
        // check for Y axis
        float newPosY = getPositionY() + (VELOCITY_MULTIPLIER * velocityY);
        tempRect = map->handleCollisionsForEntity(this, getPositionX(), newPosY);
        positionY = tempRect.y;
    }
}

Camera *Player::getCamera() { return camera; }
