#ifndef wall_hpp
#define wall_hpp

#include "../Structure.hpp"

class Wall : public Structure
{
public:
    Wall() : Structure(nullptr, -1, -1, 100, true) {}
    Wall(Texture *texture, int x, int y) : Structure(texture, x, y, 100, true) {}

    void onRightClick() override;

private:
};

#endif
