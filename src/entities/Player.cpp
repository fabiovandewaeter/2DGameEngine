#include "Player.hpp"

Player::Player() {}
Player::~Player() {}

void Player::render(SDL_Renderer *renderer)
{
    this->texture->render(renderer, positionX, positionY);
}