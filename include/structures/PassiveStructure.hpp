#ifndef passive_structure_hpp
#define passive_structure_hpp

#include "Structure.hpp"

class PassiveStructure : public Structure
{
public:
    PassiveStructure(Texture *texture, int x, int y, const Material *material, bool solid) : Structure(texture, x, y, material, solid) {}

    void onRightClick() override;

private:
};

#endif
