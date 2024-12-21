#include "items/Equipment.hpp"

Equipment::Equipment(std::string name, Texture *texture, int weight) : Item(name, texture, weight) {}

Equipment::~Equipment() {}

void Equipment::use(Entity *target) {}