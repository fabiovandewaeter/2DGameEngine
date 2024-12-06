#include "items/Item.hpp"

Item::Item(std::string name, Texture *texture)
{
    this->name = name;
    this->texture = texture;
}

Item::~Item() {}