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
    Mine() : ActiveStructure(nullptr, nullptr, nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Mine(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, int x, int y, unsigned int HP, Faction *faction, TickManager *tickManager) : ActiveStructure(texture, collisionManager, entityManager, x, y, HP, true, faction, tickManager) {};
    ~Mine();

    void update();
    std::tuple<Item *, int> getInventory();

private:
    Item *minedResource;
    int capacity;
    int quantityResource;
};

#endif
