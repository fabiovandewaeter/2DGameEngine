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
    void sendScouts(const int& x, const int& y);
    void sendArmy(const int& x, const int& y);
    
    std::vector<Entity *> entities;
};

#endif