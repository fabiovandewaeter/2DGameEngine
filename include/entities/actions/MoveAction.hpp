#ifndef move_action_hpp
#define move_action_hpp

#include "Action.hpp"

#include <vector>
#include "SDL2/SDL_rect.h"

class MoveAction : public Action
{
public:
    MoveAction(float goalX, float goalY, Entity *actor);
    void update() override;
    bool isCompleted() const override;

private:
    float goalX, goalY;
    std::vector<SDL_FPoint> path;
    size_t currentIndex;
    int stuckedCount;
    SDL_FPoint lastPosition;
    float threshold;
};

#endif
