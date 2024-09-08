#include "Tile.hpp"

Tile::Tile() {}
Tile::Tile(Texture *texture, SDL_Rect box)
{
    this->texture = texture;
    this->box = box;
}
Tile::~Tile() {}

void Tile::render(SDL_Renderer *renderer, Camera *camera)
{
    /*SDL_Rect renderBox = this->box;
    if (camera->isVisible(renderBox))
    {
        this->texture->render(renderer, renderBox);
    }*/
    this->texture->render(renderer, renderBox);
}

int Tile::getCenterX()
{
    return this->box.w / 2;
}
int Tile::getCenterY()
{
    return this->box.h / 2;
}
int Tile::getTextureId()
{
    return this->texture->getId();
}
SDL_Rect Tile::getBox()
{
    return this->box;
}