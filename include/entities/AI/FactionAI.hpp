#ifndef faction_ai_hpp
#define faction_ai_hpp

#include <vector>

class Entity;

class FactionAI
{
public:
    FactionAI();
    ~FactionAI();

    void update();
    void collectResources();
    void buildStructures();
    void buildUnits();
    void attack();

private:
    void sendScouts(int x, int y);
    void sendArmy(int x, int y);
    
    std::vector<Entity *> entities;
};

#endif