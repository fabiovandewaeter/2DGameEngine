#include "entities/Faction.hpp"

#include "entities/Entity.hpp"
#include "map/Chunk.hpp"

Faction::Faction(std::string name)
{
    this->name = name;
}
Faction::~Faction()
{
    int size = this->members.size();
    for (int i = 0; i < size; i++)
    {
        this->members[i]->setFaction(nullptr);
    }
    size = this->ownedChunks.size();
    for (int i = 0; i < size; i++)
    {
        this->ownedChunks[i]->setFaction(nullptr);
    }
}

void Faction::addMember(Entity *entity)
{
    this->members.push_back(entity);
    entity->setFaction(this);
}