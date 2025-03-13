#include "entities/behaviors/ExplorerBehavior.hpp"

#include "entities/actions/GetResourceAction.hpp"
#include "entities/actions/MoveAction.hpp"
int b = 0;
void ExplorerBehavior::update()
{
    this->entity->pushAction(new GetResourceAction("Tree", this->entity));
    // this->entity->pushAction(new MoveAction(0, 0, this->entity));

    if (b > 0)
    {
        // exit(1);
    }
    b++;
}
