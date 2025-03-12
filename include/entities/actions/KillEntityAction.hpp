#ifndef kill_entity_action_hpp
#define kill_entity_action_hpp

#include <memory>

#include "Action.hpp"

class KillEntityAction : public Action
{
public:
    KillEntityAction(Entity *attacker, Entity *target);
    void update() override;
    bool isCompleted() const override;

private:
    enum class State
    {
        INIT,      // Préparation : vérification de la cible
        MOVING,    // L'entité se déplace vers la cible
        ATTACKING, // L'entité attaque la cible
        FINISHED   // Action terminée
    };

    Entity *target;
    State state;
    std::unique_ptr<Action> moveAction;
    std::unique_ptr<Action> attackEntityAction;
};

#endif
