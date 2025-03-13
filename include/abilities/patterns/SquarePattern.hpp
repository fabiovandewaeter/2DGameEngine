#ifndef square_pattern_hpp
#define square_pattern_hpp

#include "Pattern.hpp"

#include <vector>
#include "../../systems/game_objects/EntityManager.hpp"

class SquarePattern : public Pattern
{
public:
    SquarePattern(EntityManager *entityManager, int radius);
    ~SquarePattern();

    std::vector<Entity *> getAffectedEntities(int positionX, int positionY) override;
};

#endif
