#ifndef active_structure_hpp
#define active_structure_hpp

#include "structures/Structure.hpp"

#include <vector>

#include "structures/IUpdatable.hpp"
#include "entities/Player.hpp"
#include "map/Map.hpp"

class EntityManager;
class TextureManager;
class Action;
class Faction;
class TickManager;

class ActiveStructure : public Structure, public IUpdatable
{
public:
    ActiveStructure();
    // player is the Player that place the ActiveStructure
    ActiveStructure(Texture *texture, int x, int y, unsigned int HP, bool solid, Player *player, TickManager *tickManager) : Structure{texture, x, y, HP, solid}, entityManager(player->getMap()->getEntityManager()), faction(faction), tickManager(tickManager) {};
    //ActiveStructure(Texture *texture, int x, int y, unsigned int HP, bool solid, EntityManager *entityManager, Faction *faction, TickManager *tickManager) : Structure{texture, x, y, HP, solid}, entityManager(entityManager), faction(faction), tickManager(tickManager) {};
    ~ActiveStructure();

    void onLeftClick() override;

protected:
    EntityManager *entityManager;
    bool active;
    std::vector<Action *> actions;
    Faction *faction;
    TickManager *tickManager;
};

#endif
