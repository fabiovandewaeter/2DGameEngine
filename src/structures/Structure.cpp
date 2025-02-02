#include "structures/Structure.hpp"

#include "systems/core/Camera.hpp"
#include "Texture.hpp"

Structure::~Structure() {}

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
void Structure::destroy() { delete this; }
void Structure::onCollision(Entity *entity) { std::cout << "Structure#onCollision() does nothing" << std::endl; }
void Structure::onLeftClick() { std::cout << "Structure::onLeftClick() does nothing" << std::endl; }
void Structure::onRightClick() { std::cout << "Structure::onRightClick() does nothing" << std::endl; }

SDL_Rect Structure::getHitBox() { return this->hitBox; }
int Structure::getHP() { return this->HP; }
bool Structure::isSolid() { return this->solid; }
bool Structure::isDestroyed() { return this->destroyed; }
void Structure::setX(int x) { this->hitBox.x = x; }
void Structure::setY(int y) { this->hitBox.y = y; }
void Structure::setHitBox(SDL_Rect hitBox) { this->hitBox = hitBox; }
void Structure::setTexture(Texture *texture) { this->texture = texture; }
int Structure::getTileSize() { return Tile::getTileSize(); }
