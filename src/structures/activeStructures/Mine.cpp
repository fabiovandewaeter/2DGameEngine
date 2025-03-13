#include "structures/activeStructures/Mine.hpp"

#include "map/Tile.hpp"
#include "systems/game_objects/StructureFactory.hpp"

REGISTER_CLASS(Mine)

Mine::~Mine() {}

void Mine::update()
{
    if (active && (quantityResource < capacity))
    {
        quantityResource++;
    }
}

std::tuple<Item *, int> Mine::getInventory() { return std::make_tuple(minedResource, quantityResource); }
