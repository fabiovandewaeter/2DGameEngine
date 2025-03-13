#ifndef get_resource_action_hpp
#define get_resource_action_hpp

#include <memory>

#include "Action.hpp"
#include "systems/algorithms/AstarPathFinding.hpp"

class GetResourceAction : public Action
{
public:
    GetResourceAction(const std::string &resourceToGet, Entity *actor);
    void update() override;
    bool isCompleted() const override;

private:
    enum class State
    {
        INIT,     // Vérification et initialisation de la cible
        MOVING,   // Déplacement vers la structure cible
        BREAKING, // Action de casse sur la structure
        FINISHED  // Action terminée
    };

    std::string resourceToGet;
    std::pair<float, float> destination;
    State state;
    std::unique_ptr<Action> moveAction;
    std::unique_ptr<Action> breakStructureAction;
};

#endif
