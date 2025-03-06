#include "entities/actions/Action.hpp"

void Action::executeSubActions()
{
    if (this->subActions.empty())
    {
        this->completed = true;
    }
    else
    {
        Action *currentSubAction = this->subActions.front();
        currentSubAction->execute();
        if (currentSubAction->isCompleted())
        {
            delete currentSubAction;
            this->subActions.pop();
        }
    }
}

bool Action::isCompleted() { return this->completed; }
