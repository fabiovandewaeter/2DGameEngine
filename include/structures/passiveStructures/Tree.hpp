#ifndef tree_hpp
#define tree_hpp

#include "../Structure.hpp"

class Tree : public Structure
{
public:
    Tree() : Structure(nullptr, -1, -1, 100, true, nullptr, nullptr) {}
    Tree(std::string textureName, float x, float y, Player *placedBy, TickManager *tickManager) : Structure(textureName, x, y, 100, true, placedBy, tickManager) {}

    void onRightClick() override;
    std::string getClassName() override { return "Tree"; }

private:
};

#endif
