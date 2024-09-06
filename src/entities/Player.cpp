#include "Player.hpp"

Player::Player() {}
Player::~Player() {}

void Player::render2(SDL_Renderer *renderer, double scale)
{
    this->texture->render(renderer, this->hitBox.x, this->hitBox.y, scale);
}