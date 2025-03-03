#ifndef move_action_hpp
#define move_action_hpp

#include "Action.hpp"

#include <vector>
#include "SDL2/SDL_rect.h"

#include "systems/algorithms/AstarPathFinding.hpp"

class MoveAction : public Action
{
public:
    MoveAction(float x, float y, Entity *entity) : Action(entity), path(AstarPathFinding::findPath(this->entity->getMap(), entity->getPositionX(), entity->getPositionY(), x, y)), currentIndex(0) {};
    void execute() override;
    bool isCompleted() override;

private:
    float x, y;
    std::vector<SDL_FPoint> path;
    int currentIndex;
};

#endif
