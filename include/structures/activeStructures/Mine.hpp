#ifndef mine_hpp
#define mine_hpp

#include "ActiveStructure.hpp"

class Faction;
class Tile;
class Item;

class Mine : public ActiveStructure
{
public:
    Mine(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, SDL_Rect hitBox, unsigned int HP, Faction *faction, Tile *minedTile);
    ~Mine();

    void update();

private:
    Item *minedResource;
    int capacity;
    int quantityResource;
};

#endif