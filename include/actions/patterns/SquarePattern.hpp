#ifndef square_pattern_hpp
#define square_pattern_hpp

#include "Pattern.hpp"

#include <vector>
#include "../../systems/EntityManager.hpp"

class SquarePattern : public Pattern
{
public:
    SquarePattern(EntityManager *entityManager, const int& radius);
    ~SquarePattern();

    std::vector<Entity *> getAffectedEntities(const int& x, const int& y) override;
};

#endif