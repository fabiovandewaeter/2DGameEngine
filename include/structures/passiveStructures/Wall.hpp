#ifndef wall_hpp
#define wall_hpp

#include "../PassiveStructure.hpp"

class Wall : public PassiveStructure
{
public:
    Wall::Wall() : PassiveStructure("Wall", -1, -1, nullptr, true) {}
    Wall::Wall(TextureManager *textureManager, int x, int y, const Material *material) : PassiveStructure(textureManager->getTexture("Wall"), x, y, material, true) {}

private:
};

#endif
