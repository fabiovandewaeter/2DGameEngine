#ifndef heal_effect_hpp
#define heal_effect_hpp

#include "Effect.hpp"

class HealEffect : public Effect
{
public:
    HealEffect(const int& hp);
    ~HealEffect();

    void applyEffect(Entity *entity) override;

private:
    int hp;
};

#endif