#ifndef faction_hpp
#define faction_hpp

#include <string>
#include <vector>

class Entity;
class Chunk;

class Faction
{
public:
    Faction(std::string name) : name(name), homeCoordinates({0, 0}) {}
    ~Faction();

    // getter
    std::pair<float, float> getHomeCoordinates();

    // setter
    void addMember(Entity *entity);

private:
    std::string name;
    std::vector<Entity *> members;
    std::vector<Chunk *> ownedChunks;

    std::pair<float, float> homeCoordinates;
};

#endif
