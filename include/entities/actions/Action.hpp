#ifndef action_hpp
#define action_hpp

#include <string>
#include <queue>

#include "entities/Entity.hpp"

class Entity;

class Action
{
public:
    Action(Entity *entity) : entity(entity), completed(false), subActionsIndex(0) {}
    ~Action() = default;
    // execute the Action ; the execution can take multiple ticks and will make isCompleted() returns true when finished
    virtual void execute() = 0;
    bool isCompleted();

protected:
    Entity *entity;
    bool completed;
    std::queue<Action *> subActions;
    int subActionsIndex;

    void executeSubActions();
};

#endif
