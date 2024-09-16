#include "StaticObject.hpp"

StaticObject::StaticObject() {}
StaticObject::StaticObject(Texture *texture, SDL_Rect hitBox, const char *name, unsigned int HP)
{
    init(texture, hitBox, name, HP);
}
StaticObject::~StaticObject() {}

void StaticObject::init(Texture *texture, SDL_Rect hitBox, const char *name, unsigned int HP)
{
    this->texture = texture;
    this->hitBox = hitBox;
    this->solid = true;
    this->name = name;
    this->HP = HP;
}

void StaticObject::render(Camera *camera)
{
    SDL_Rect renderBox = this->hitBox;
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        this->texture->render(renderBox);
    }
}

void StaticObject::destroy()
{
    delete this;
}

SDL_Rect StaticObject::getHitBox()
{
    return this->hitBox;
}
bool StaticObject::isSolid()
{
    return this->solid;
}
void StaticObject::setHitBox(SDL_Rect hitBox){
    this->hitBox = hitBox;
}