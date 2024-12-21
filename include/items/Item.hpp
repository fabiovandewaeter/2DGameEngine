#ifndef item_hpp
#define item_hpp

#include <string>

class Texture;
class Entity;

class Item
{
public:
    Item(std::string name, Texture *texture, int weight);
    ~Item();

    virtual void attack(Entity* target) = 0;
    virtual void consume(Entity* target) = 0;
    virtual bool isEquippable() = 0;

private:
    std::string name;
    Texture *texture;
    int weight;
};

#endif