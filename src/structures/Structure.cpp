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

bool Structure::isSolid() const { return this->solid; }
bool Structure::isDestroyed() const { return this->destroyed; }

// getter
int Structure::getHP() const { return this->HP; }
float Structure::getPositionX() const { return this->x; }
float Structure::getPositionY() const { return this->y; }
SDL_FRect Structure::getHitBox() const { return {this->x, this->y, this->width, this->height}; }
std::string Structure::getTextureName() const { return this->textureName; }
int Structure::getTileSize() { return Tile::getTileSize(); }

// setter
void Structure::setHitBox(SDL_FRect hitBox)
{
    this->x = hitBox.x;
    this->y = hitBox.y;
    this->width = hitBox.w;
    this->height = hitBox.h;
}

void Structure::setX(float x) { this->x = x; }
void Structure::setY(float y) { this->y = y; }
void Structure::setTextureName(std::string textureName) { this->textureName = textureName; }
