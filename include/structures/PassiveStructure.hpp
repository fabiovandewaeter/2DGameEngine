#ifndef passive_structure_hpp
#define passive_structure_hpp

#include "structures/Structure.hpp"

class PassiveStructure : public Structure
{
public:
    PassiveStructure(Texture *texture, int x, int y, int HP, bool solid) : Structure(texture, x, y, HP, solid) {}

    void onRightClick() override;

private:
};

#endif
