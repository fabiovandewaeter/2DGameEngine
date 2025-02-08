#ifndef action_hpp
#define action_hpp

#include <string>

class Entity;

class Action
{
public:
    virtual void execute(Entity *entity) = 0;
    virtual bool isCompleted() = 0;

private:
};

#endif
