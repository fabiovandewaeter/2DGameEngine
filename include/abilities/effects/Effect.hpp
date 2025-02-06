#ifndef effect_hpp
#define effect_hpp

#include <vector>

class Entity;

class Effect
{
public:
    ~Effect() = default;

    virtual void applyEffect(Entity *entity) = 0;

private:
};

#endif
