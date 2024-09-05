#include "Player.hpp"

Player::Player() {}
Player::~Player() {}

void Player::render(SDL_Renderer *renderer, int cameraX, int cameraY)
{
    std::cout << positionX << " " << positionY << std::endl;
    this->texture->render(renderer, positionX, positionY);
}