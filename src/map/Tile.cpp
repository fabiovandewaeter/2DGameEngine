#include "Tile.hpp"

Tile::Tile(Texture *texture, SDL_Rect box)
{
    this->texture = texture;
    this->box = box;
}
Tile::~Tile() {}


void Tile::render(SDL_Renderer *renderer, int cameraCenterX, int cameraCenterY, int cameraPositionX, int cameraPositionY, double scale)
{
    this->texture->render(renderer, (cameraCenterX-cameraPositionX*scale) - (this->box.x * scale), (cameraCenterY-cameraPositionY*scale) - (this->box.y * scale), this->box.w, this->box.h, scale);
}

int Tile::getCenterX(){
    return this->box.w/2;
}
int Tile::getCenterY(){
    return this->box.h/2;
}
int Tile::getTextureId(){
    return this->texture->getId();
}