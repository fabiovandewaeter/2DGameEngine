#include "items/Resource.hpp"

Resource::Resource(std::string name, Texture *texture, int weight) : Item(name, texture, weight) {}

Resource::~Resource() {}

void Resource::use(Entity *target) {}