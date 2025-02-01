#ifndef active_structure_hpp
#define active_structure_hpp

#include "structures/Structure.hpp"
#include "structures/IUpdatable.hpp"
#include <vector>

class EntityManager;
class TextureManager;
class Map;
class Action;
class Faction;
class TickManager;

class ActiveStructure : public Structure, public IUpdatable
{
public:
    ActiveStructure();
    ActiveStructure(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, int x, int y, unsigned int HP, bool solid, Faction *faction, TickManager *tickManager) : Structure{texture, x, y, HP, solid}, collisionManager(collisionManager), entityManager(entityManager), faction(faction), tickManager(tickManager) {};
    ~ActiveStructure();

    void onLeftClick() override;

protected:
    CollisionManager *collisionManager;
    EntityManager *entityManager;
    bool active;
    std::vector<Action *> actions;
    Faction *faction;
    TickManager *tickManager;
};

#endif
