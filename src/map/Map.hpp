#ifndef map_hpp
#define map_hpp

#include <vector>
#include "Tile.hpp"

class Map
{
public:
    Map();
    ~Map();
private:
    std::vector<Tile *> tiles;
};

#endif