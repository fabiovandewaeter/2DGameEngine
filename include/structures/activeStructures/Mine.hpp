#ifndef mine_hpp
#define mine_hpp

#include <tuple>

#include "ActiveStructure.hpp"

class Faction;
class Tile;
class Item;

class Mine : public ActiveStructure
{
public:
    Mine(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, SDL_Rect hitBox, unsigned int HP, Faction *faction, Tile *minedTile, TickManager *tickManager);
    ~Mine();

    void update();
    std::tuple<Item *, int> getInventory();

private:
    Item *minedResource;
    int capacity;
    int quantityResource;
};

#endif
