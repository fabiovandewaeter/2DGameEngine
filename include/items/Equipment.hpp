#ifndef equipment_hpp
#define equipment_hpp

#include <string>

#include "Item.hpp"

class Equipment : public Item
{
public:
    Equipment(std::string name, Texture *texture, int weight);
    ~Equipment();

    void attack(Entity *target) override;
    void consume(Entity *target) override;
    bool isEquippable() override { return true; }

private:
};

#endif