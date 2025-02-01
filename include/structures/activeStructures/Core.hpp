#ifndef core_hpp
#define core_hpp

#include "../ActiveStructure.hpp"

class Core : public ActiveStructure
{
public:
    Core() : ActiveStructure(nullptr, nullptr, nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, int x, int y, unsigned int HP, Faction *faction, TickManager *tickManager) : ActiveStructure(texture, collisionManager, entityManager, x, y, HP, true, faction, tickManager) {};

    void update() override;

private:
    void spawnEntities();
    std::vector<SDL_Rect> getPotentialSpawnTiles(SDL_Rect entityHitBox);
};

#endif
