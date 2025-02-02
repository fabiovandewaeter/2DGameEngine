#include "entities/Player.hpp"

#include "systems/core/Camera.hpp"
#include "map/Map.hpp"

// 1 if false and sprintVelocity if true
int sprint2 = 1;
int leftVelX2 = 0, rightVelX2 = 0, upVelY2 = 0, downVelY2 = 0;

void Player::handleEvents(SDL_Event *event, GUIManager *guiManager, MouseManager *mouseManager)
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
            this->hitBox.x = 0;
            this->hitBox.y = 0;
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
    if (!guiManager->handleEvents(event))
    {
        mouseManager->handleEvents(event, this); // doesnt click on the map if click on GUI
    }
}
void Player::update()
{
    this->camera->update();
    Entity::update(this->map);
}
void Player::render()
{
    this->map->render(this);
    Entity::render(this->camera);
}

void Player::setPosition(int x, int y)
{
    this->hitBox.x = x;
    this->hitBox.y = y;
}
Map *Player::getMap() { return this->map; }
Camera *Player::getCamera() { return this->camera; }
