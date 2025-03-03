#ifndef active_structure_hpp
#define active_structure_hpp

#include "structures/Structure.hpp"

#include <vector>

#include "structures/IUpdatable.hpp"
#include "entities/Player.hpp"
#include "map/Map.hpp"

class EntityManager;
class TextureManager;
class Ability;
class Faction;
class TickManager;

class ActiveStructure : public Structure, public IUpdatable
{
public:
    ActiveStructure();
    // player is the Player that place the ActiveStructure
    ActiveStructure(Texture *texture, float x, float y, int HP, bool solid, Player *placedBy, TickManager *tickManager) : Structure{texture, x, y, HP, solid, placedBy, tickManager}, map(placedBy->getMap()), entityManager(placedBy->getMap()->getEntityManager()), faction(faction), tickManager(tickManager) {};
    ~ActiveStructure();

    void onLeftClick() override;

protected:
    Map *map;
    EntityManager *entityManager;
    bool active;
    std::vector<Ability *> abilities;
    Faction *faction;
    TickManager *tickManager;
};

#endif
