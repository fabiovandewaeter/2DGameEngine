#include "items/Item.hpp"

Item::Item(std::string name, Texture *texture, int weight, bool equippable)
{
    this->name = name;
    this->texture = texture;
    this->weight = weight;
    this->equippable = equippable;
}

Item::~Item() {}

void Item::attack(Entity *source, Entity *target) {}
void Item::consume(Entity *source, Entity *target) {}
bool Item::isEquippable() { return this->equippable; }