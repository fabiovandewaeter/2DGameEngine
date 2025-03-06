#ifndef get_resource_action_hpp
#define get_resource_action_hpp

#include "Action.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"

class GetResourceAction : public Action
{
public:
    GetResourceAction(std::string resourceToGet, Entity *entity);
    void execute() override;

private:
    std::string resourceToGet;
};

#endif
