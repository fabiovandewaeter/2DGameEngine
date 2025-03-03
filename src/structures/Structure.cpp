#include "structures/Structure.hpp"

#include "systems/core/Camera.hpp"
#include "Texture.hpp"

Structure::~Structure() {}

void Structure::render(Camera *camera)
{
    SDL_FRect renderBox = {this->x, this->y, this->width, this->height};
    SDL_Rect newRenderBox = camera->convertInGameToCameraCoordinates(renderBox);
    if (camera->isVisibleOnScreen(newRenderBox))
    {
        camera->render(this->texture, newRenderBox);
    }
}

void Structure::update() {}
void Structure::destroy() { delete this; }
void Structure::onCollision(Entity *entity) { std::cout << "Structure#onCollision() does nothing" << std::endl; }
void Structure::onLeftClick() { std::cout << "Structure::onLeftClick() does nothing" << std::endl; }
void Structure::onRightClick() { std::cout << "Structure::onRightClick() does nothing" << std::endl; }

SDL_FRect Structure::getHitBox() { return {this->x, this->y, this->width, this->height}; }
int Structure::getHP() { return this->HP; }
bool Structure::isSolid() { return this->solid; }
bool Structure::isDestroyed() { return this->destroyed; }
void Structure::setHitBox(SDL_FRect hitBox)
{
    this->x = hitBox.x;
    this->y = hitBox.y;
    this->width = hitBox.w;
    this->height = hitBox.h;
}
void Structure::setX(float x) { this->x = x; }
void Structure::setY(float y) { this->y = y; }
void Structure::setTexture(Texture *texture) { this->texture = texture; }
int Structure::getTileSize() { return Tile::getTileSize(); }
float Structure::getPositionX()
{
    return this->x;
}
float Structure::getPositionY()
{
    std::cout << "ICI" << std::endl;
    this->y = 4.9999990000;
    return this->y;
}
