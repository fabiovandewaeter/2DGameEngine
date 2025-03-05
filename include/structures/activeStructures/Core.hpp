#ifndef core_hpp
#define core_hpp

#include "../ActiveStructure.hpp"

class Core : public ActiveStructure
{
public:
    Core() : ActiveStructure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Core(std::string textureName, float x, float y, Player *placedBy, TickManager *tickManager) : ActiveStructure{textureName, x, y, 100, true, placedBy, tickManager} {};

    void update() override;
    std::string getClassName() override { return "Core"; }

private:
    void spawnEntities();
    std::vector<SDL_FRect> getPotentialSpawnTiles(SDL_FRect entityHitBox);
};

#endif
