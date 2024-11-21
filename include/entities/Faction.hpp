#ifndef faction_hpp
#define faction_hpp

#include <string>
#include <vector>

class Entity;
class Chunk;

class Faction
{
public:
    Faction(std::string name);
    ~Faction();

    void addMember(Entity *entity);

private:
    std::string name;
    std::vector<Entity *> members;
    std::vector<Chunk *> ownedChunks;
};

#endif