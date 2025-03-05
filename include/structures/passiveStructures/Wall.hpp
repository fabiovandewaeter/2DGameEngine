#ifndef wall_hpp
#define wall_hpp

#include "../Structure.hpp"

class Wall : public Structure
{
public:
    Wall() : Structure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Wall(std::string textureName, float x, float y, Player *placedBy, TickManager *tickManager) : Structure(textureName, x, y, 100, true, placedBy, tickManager) {}

    void onRightClick() override;
    std::string getClassName() override { return "Wall"; }

private:
};

#endif
