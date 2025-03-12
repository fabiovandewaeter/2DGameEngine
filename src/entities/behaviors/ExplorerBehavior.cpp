#include "entities/behaviors/ExplorerBehavior.hpp"

#include "entities/actions/GetResourceAction.hpp"
#include "entities/actions/MoveAction.hpp"
void ExplorerBehavior::execute()
{
    this->entity->pushAction(new GetResourceAction("Tree", this->entity));
    // this->entity->pushAction(new MoveAction(0, 0, this->entity));
}
