#ifndef core_hpp
#define core_hpp

#include "../ActiveStructure.hpp"

class Core : public ActiveStructure
{
public:
    Core() : ActiveStructure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Core(Texture *texture, int x, int y, Player *placedBy, TickManager *tickManager) : ActiveStructure{texture, x, y, 100, true, placedBy, tickManager} {};

    void update() override;
    std::string getClassName() override { return "Core"; }

private:
    void spawnEntities();
    std::vector<SDL_Rect> getPotentialSpawnTiles(SDL_Rect entityHitBox);
};

#endif
