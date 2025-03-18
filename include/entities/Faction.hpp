#ifndef faction_hpp
#define faction_hpp

#include <string>
#include <vector>

class Entity;
class Chunk;

class Faction
{
public:
    Faction(std::string name) : name(name), score(0), homeCoordinates({0, 0}) {}
    ~Faction();

    // getter
    std::pair<float, float> getHomeCoordinates();
    // return true if is allied with the faction
    bool isAlliedWith(Faction *faction);
    long long getScore();

    // setter
    void addMember(Entity *entity);

private:
    std::string name;
    std::vector<Entity *> members;
    std::vector<Chunk *> ownedChunks;
    long long score;

    std::pair<float, float> homeCoordinates;
};

#endif
