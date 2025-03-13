#include "structures/Structure.hpp"

#include "systems/core/Camera.hpp"
#include "Texture.hpp"

Structure::~Structure() {}

void Structure::render(Camera *camera) { camera->render(this); }

void Structure::update() {}
void Structure::destroy() { delete this; }
void Structure::onCollision(Entity *entity) { std::cout << "Structure#onCollision() does nothing" << std::endl; }
void Structure::onLeftClick() { std::cout << "Structure::onLeftClick() does nothing" << std::endl; }
void Structure::onRightClick() { std::cout << "Structure::onRightClick() does nothing" << std::endl; }

bool Structure::isSolid() const { return solid; }
bool Structure::isDestroyed() const { return destroyed; }

// getter
int Structure::getHP() const { return HP; }
float Structure::getPositionX() const { return positionX; }
float Structure::getPositionY() const { return positionY; }
SDL_FRect Structure::getHitBox() const { return {positionX, positionY, width, height}; }
std::string Structure::getTextureName() const { return textureName; }
int Structure::getTileSize() { return Tile::getTileSize(); }

// setter
void Structure::setHitBox(SDL_FRect hitBox)
{
    positionX = hitBox.x;
    positionY = hitBox.y;
    width = hitBox.w;
    height = hitBox.h;
}

void Structure::setX(float positionX) { this->positionX = positionX; }
void Structure::setY(float positionY) { this->positionY = positionY; }
void Structure::setTextureName(std::string textureName) { this->textureName = textureName; }
