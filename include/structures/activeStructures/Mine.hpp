#ifndef mine_hpp
#define mine_hpp

#include <tuple>

#include "../ActiveStructure.hpp"

class Faction;
class Tile;
class Item;

class Mine : public ActiveStructure
{
public:
    Mine() : ActiveStructure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Mine(Texture *texture, int x, int y, Player *placedBy, TickManager *tickManager) : ActiveStructure{texture, x, y, 100, true, placedBy, tickManager} {};
    ~Mine();

    void update();
    std::tuple<Item *, int> getInventory();
    std::string getClassName() override { return "Mine"; }

private:
    Item *minedResource;
    int capacity;
    int quantityResource;
};

#endif
