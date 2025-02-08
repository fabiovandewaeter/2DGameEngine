#ifndef move_action_hpp
#define move_action_hpp

#include "Action.hpp"

#include <vector>
#include "SDL2/SDL_rect.h"

class MoveAction : public Action
{
public:
    MoveAction(std::vector<SDL_Point> *path) : path(path), currentIndex(0) {};
    void execute(Entity *entity) override;
    bool isCompleted() override;

private:
    std::vector<SDL_Point> *path;
    int currentIndex;
};

#endif
