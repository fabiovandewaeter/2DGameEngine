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
    Mine(std::string textureName, float positionX, float positionY, Player *placedBy, TickManager *tickManager) : ActiveStructure{textureName, positionX, positionY, 100, true, placedBy, tickManager} {};
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
