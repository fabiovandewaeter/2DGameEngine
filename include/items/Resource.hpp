#ifndef resource_hpp
#define resource_hpp

#include <string>

#include "Item.hpp"

class Resource : public Item
{
public:
    Resource(std::string name, Texture *texture, int weight);
    ~Resource();

    void attack(Entity *target) override;
    void consume(Entity *target) override;
    bool isEquippable() override { return false; }

private:
};

#endif
