#include "entities/actions/BreakStructureAction.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "structures/Structure.hpp"

BreakStructureAction::BreakStructureAction(float goalX, float goalY, Entity *actor)
    : Action(actor), goalX(goalX), goalY(goalY), structureBroken(false)
{
}

void BreakStructureAction::update()
{
    // Si l'action a déjà été exécutée, on ne fait rien.
    if (structureBroken)
        return;

    float threshold = actor->getRange() + 1;
    float dx = goalX - actor->getPositionX();
    float dy = goalY - actor->getPositionY();
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= threshold)
    {
        auto chunk = actor->getMap()->getChunk(goalX, goalY);
        if (chunk != nullptr)
        {
            auto structure = chunk->breakStructure(goalX, goalY);
            if (structure != nullptr)
            {
                actor->giveStructure(structure);
            }
        }
    }
    else
    {
        std::cerr << "ERROR : BreakStructureAction::update() => Entity not in range" << std::endl;
    }

    structureBroken = true;
}

bool BreakStructureAction::isCompleted() const { return structureBroken; }
