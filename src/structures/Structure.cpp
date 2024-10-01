#include "Structure.hpp"
#include "../systems/Camera.hpp"
#include "../Texture.hpp"

Structure::Structure() {}
/*Structure::Structure(Texture *texture, unsigned int HP, bool solid)
{
    init(texture, HP, solid);
}
Structure::Structure(Texture *texture, SDL_Rect hitBox, unsigned int HP, bool solid)
{
    init(texture, hitBox, HP, solid);
}*/
Structure::~Structure() {}

void Structure::init(Texture *texture, CollisionManager *collisionManager, unsigned int range, unsigned int HP, bool solid)
{
    this->texture = texture;
    this->collisionManager = collisionManager;
    this->HP = HP;
    this->solid = solid;
    this->range = range;
    this->active = true;
}
void Structure::init(Texture *texture, CollisionManager *collisionManager, SDL_Rect hitBox, unsigned int range, unsigned int HP, bool solid)
{
    init(texture, collisionManager, range, HP, solid);
    this->hitBox = hitBox;
}

void Structure::render(Camera *camera)
{
    SDL_Rect renderBox = this->hitBox;
    camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisible(renderBox))
    {
        this->texture->render(renderBox);
    }
}

void Structure::update() {}
void Structure::destroy()
{
    delete this;
}
void Structure::onCollision(Entity *entity)
{
    std::cout << "Structure#onCollision()" << std::endl;
}

SDL_Rect Structure::getHitBox()
{
    return this->hitBox;
}
bool Structure::isSolid()
{
    return this->solid;
}
bool Structure::isActive()
{
    return this->active;
}
void Structure::setHitBox(SDL_Rect hitBox)
{
    this->hitBox = hitBox;
}
description Structure::getDescription(){
    return this->description;
}