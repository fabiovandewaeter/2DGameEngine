#ifndef move_action_hpp
#define move_action_hpp

#include "Action.hpp"

#include <vector>
#include "SDL2/SDL_rect.h"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"

class MoveAction : public Action
{
public:
    MoveAction(float goalX, float goalY, Entity *entity) : Action(entity), goalX(goalX), goalY(goalY), path(AstarPathFinding::findPath(this->entity->getMap(), entity->getPositionX(), entity->getPositionY(), goalX, goalY)), currentIndex(0), stuckedCount(0), threshold((this->entity->getMap()->getChunk(this->goalX, this->goalY)->isStructure(this->goalX, this->goalY)) ? this->entity->getRange() + 1 : 0.0001f), lastPosition({0, 0}) {}
    void execute() override;

private:
    float goalX, goalY;
    std::vector<SDL_FPoint> path;
    int currentIndex;
    int stuckedCount;
    float threshold;
    SDL_FPoint lastPosition;
};

#endif
