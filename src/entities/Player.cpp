#include "Player.hpp"

Player::Player(){}
Player::~Player(){
    printf("DAZDAZ");
    texture.free();
}

void Player::init(LTexture texture, SDL_Rect position){
    this->texture = texture;
    this->position = position;
    this->velX = 0;
    this-> velY = 0;
}

bool Player::update(){
    return move();
}

bool Player::move(){
    bool success = true;

    // EXAMPLE: check if he stunned ...
    position.x += velX;
    position.y += velY;

    return success;
}

void Player::render(SDL_Renderer *renderer){
    texture.render(position.x, position.y, renderer);
    std::cout << position.x << " " << position.y << " " << std::endl;
}

void Player::setVelocity(int velocityX, int velocityY)
{
    this->velX = velocityX;
    this->velY = velocityY;
}