#ifndef item_hpp
#define item_hpp

#include <string>

class Texture;

class Item
{
public:
    Item(std::string name, Texture *texture);
    ~Item();

private:
    std::string name;
    Texture *texture;
};

#endif