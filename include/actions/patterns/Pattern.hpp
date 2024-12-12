#ifndef pattern_hpp
#define pattern_hpp

#include <vector>

class Entity;
class EntityManager;

class Pattern
{
public:
    Pattern(EntityManager *entityManager, const int& radius);
    virtual ~Pattern();

    virtual std::vector<Entity *> getAffectedEntities(const int& x, const int& y) = 0;

protected:
    EntityManager *entityManager;
    int radius;
};

#endif