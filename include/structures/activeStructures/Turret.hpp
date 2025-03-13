#ifndef turret_hpp
#define turret_hpp

#include "../ActiveStructure.hpp"

class Turret : public ActiveStructure
{
public:
    Turret() : ActiveStructure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Turret(std::string textureName, float positionX, float positionY, Player *placedBy, TickManager *tickManager) : ActiveStructure{textureName, positionX, positionY, 100, true, placedBy, tickManager} {};

    void update() override;
    std::string getClassName() override { return "Turret"; }
};

#endif
