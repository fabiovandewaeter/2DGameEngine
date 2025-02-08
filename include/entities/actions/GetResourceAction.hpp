#ifndef get_resource_action_hpp
#define get_resource_action_hpp

#include "Action.hpp"

class GetResourceAction : public Action
{
public:
    GetResourceAction(std::string resourceToGet) : resourceToGet(resourceToGet) {};
    void execute(Entity *entity) override;
    bool isCompleted() override;

private:
    std::string resourceToGet;
};

#endif
