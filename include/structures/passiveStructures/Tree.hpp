#ifndef tree_hpp
#define tree_hpp

#include "../Structure.hpp"

class Tree : public Structure
{
public:
    Tree() : Structure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Tree(Texture *texture, int x, int y, Player *placedBy, TickManager *tickManager) : Structure(texture, x, y, 100, true, placedBy, tickManager) {}

    void onRightClick() override;
    std::string getClassName() override { return "Tree"; }

private:
};

#endif
