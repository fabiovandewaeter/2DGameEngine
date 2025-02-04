#ifndef turret_hpp
#define turret_hpp

#include "../ActiveStructure.hpp"

class Turret : public ActiveStructure
{
public:
    Turret() : ActiveStructure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Turret(Texture *texture, int x, int y, Player *placedBy, TickManager *tickManager) : ActiveStructure{texture, x, y, 100, true, placedBy, tickManager} {};

    void update() override;
};

#endif
