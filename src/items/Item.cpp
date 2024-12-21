#include "items/Item.hpp"

Item::Item(std::string name, Texture *texture, int weight)
{
    this->name = name;
    this->texture = texture;
    this->weight = weight;
}

Item::~Item() {}