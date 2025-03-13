#ifndef damage_effect_hpp
#define damage_effect_hpp

#include "Effect.hpp"

class DamageEffect : public Effect
{
public:
    DamageEffect(int damage) : damage(damage) {}
    ~DamageEffect() = default;

    void applyEffect(Entity *entity) override;

private:
    int damage;
};

#endif
