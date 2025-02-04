#ifndef wall_hpp
#define wall_hpp

#include "../Structure.hpp"

class Wall : public Structure
{
public:
    Wall() : Structure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Wall(Texture *texture, int x, int y, Player *player, TickManager *tickManager) : Structure(texture, x, y, 100, true, player, tickManager) {}

    void onRightClick() override;

private:
};

#endif
