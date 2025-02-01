#ifndef turret_hpp
#define turret_hpp

#include "../ActiveStructure.hpp"

class Turret : public ActiveStructure
{
public:
    Turret() : ActiveStructure(nullptr, nullptr, nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Turret(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, int x, int y, unsigned int HP, Faction *faction, TickManager *tickManager) : ActiveStructure(texture, collisionManager, entityManager, x, y, HP, true, faction, tickManager) {};

    void update() override;
};

#endif
