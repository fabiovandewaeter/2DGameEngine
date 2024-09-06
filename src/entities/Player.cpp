#include "Player.hpp"

const double BASE_SCALE2 = 1.0;
// 1 if false and sprintVelocity if true
int sprint2 = 1;
int leftVelX2 = 0, rightVelX2 = 0, upVelY2 = 0, downVelY2 = 0;

Player::Player() {}
Player::~Player() {}

void Player::handleEvents(SDL_Event *event)
{
    // If a key was pressed
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        // Adjust the velocity
        switch (event->key.keysym.sym)
        {
        case SDLK_i:
            upVelY2 = -this->velocity;
            break;
        case SDLK_k:
            downVelY2 = -this->velocity;
            break;
        case SDLK_j:
            leftVelX2 = -this->velocity;
            break;
        case SDLK_l:
            rightVelX2 = -this->velocity;
            break;
        case SDLK_LSHIFT:
            sprint2 = 2;
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
            sprint2 = 1;
            break;
        }
        this->velX = sprint2 * (rightVelX2 - leftVelX2);
        this->velY = sprint2 * (downVelY2 - upVelY2);
    }
}
void Player::render2(SDL_Renderer *renderer, double scale)
{
    this->texture->render(renderer, this->hitBox.x, this->hitBox.y, scale);
}

void Player::setPosition(int x, int y){
    this->hitBox.x = x;
    this->hitBox.y = y;
}