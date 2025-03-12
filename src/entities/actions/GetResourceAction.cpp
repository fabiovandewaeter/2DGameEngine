#include "entities/actions/GetResourceAction.hpp"

#include "systems/algorithms/AstarPathFinding.hpp"
#include "structures/Structure.hpp"
#include "map/Map.hpp"
#include "entities/actions/MoveAction.hpp"
#include "entities/actions/BreakStructureAction.hpp"

GetResourceAction::GetResourceAction(const std::string &resourceToGet, Entity *actor)
    : Action(actor), resourceToGet(resourceToGet), state(State::INIT)
{
    // Recherche de la structure la plus proche contenant la ressource demandée
    Structure *targetedStructure = actor->getMap()->findClosestStructure(this->resourceToGet, actor);
    if (targetedStructure)
    {
        destination = {targetedStructure->getPositionX(), targetedStructure->getPositionY()};
        // Initialisation de la sous-action de déplacement
        moveAction = std::make_unique<MoveAction>(destination.first, destination.second, actor);
        state = State::MOVING;
    }
    else
    {
        std::cout << "GetResourceAction::GetResourceAction() : " << this->resourceToGet << " not found on the Map" << std::endl;
        state = State::FINISHED;
    }
}

void GetResourceAction::update()
{
    switch (state)
    {
    case State::MOVING:
        if (moveAction)
        {
            moveAction->update();
            if (moveAction->isCompleted())
            {
                // Une fois le déplacement terminé, on passe à l'action de casse
                breakStructureAction = std::make_unique<BreakStructureAction>(destination.first, destination.second, actor);
                state = State::BREAKING;
            }
        }
        break;

    case State::BREAKING:
        if (breakStructureAction)
        {
            breakStructureAction->update();
            if (breakStructureAction->isCompleted())
            {
                state = State::FINISHED;
            }
        }
        break;

    default:
        break;
    }
}

bool GetResourceAction::isCompleted() const { return state == State::FINISHED; }
