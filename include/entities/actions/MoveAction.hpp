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
    MoveAction(float goalX, float goalY, Entity *entity);
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
