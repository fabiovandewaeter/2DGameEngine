#include "entities/Faction.hpp"

#include "entities/Entity.hpp"
#include "map/Chunk.hpp"

Faction::~Faction()
{
    int size = members.size();
    for (int i = 0; i < size; i++)
    {
        members[i]->setFaction(nullptr);
    }
    size = ownedChunks.size();
    for (int i = 0; i < size; i++)
    {
        ownedChunks[i]->setFaction(nullptr);
    }
}

// getter
std::pair<float, float> Faction::getHomeCoordinates() { return homeCoordinates; }
bool Faction::isAlliedWith(Faction *faction) { return false; }
long long Faction::getScore() { return score; }

// setter
void Faction::addMember(Entity *entity)
{
    members.push_back(entity);
    entity->setFaction(this);
}
