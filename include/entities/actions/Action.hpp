#ifndef action_hpp
#define action_hpp

#include <string>
#include <queue>

#include "entities/Entity.hpp"

class Entity;

class Action
{
public:
    Action(Entity *actor) : actor(actor) {}
    virtual ~Action() = default;
    // execute the Action ; the execution can take multiple ticks and will make isCompleted() returns true when finished
    virtual void update() = 0;
    virtual bool isCompleted() const = 0;

protected:
    Entity *actor;
};

#endif
