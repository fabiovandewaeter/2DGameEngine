#include "Map.hpp"

Map::Map(){}
Map::~Map(){
    for (Tile* tile : this->tiles){
        delete tile;
    }
    tiles.clear();
}