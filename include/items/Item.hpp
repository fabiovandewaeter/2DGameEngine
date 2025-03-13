#ifndef item_hpp
#define item_hpp

#include <string>

class Texture;
class Entity;

class Item
{
public:
    Item(std::string name, Texture *texture, int weight, bool equippable) : name(name), texture(texture), weight(weight), equippable(equippable) {}
    ~Item() = default;

    void attack(Entity *source, Entity *target);
    void consume(Entity *source, Entity *target);
    bool isEquippable();

private:
    std::string name;
    Texture *texture;
    int weight;
    bool equippable;
};

#endif
