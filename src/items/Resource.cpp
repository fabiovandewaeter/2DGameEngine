#include "items/Resource.hpp"

Resource::Resource(std::string name, Texture *texture)
{
    this->name = name;
    this->texture = texture;
}

Resource::~Resource() {}