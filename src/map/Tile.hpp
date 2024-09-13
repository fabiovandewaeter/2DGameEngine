#ifndef tile_hpp
#define tile_hpp

#include <vector>
#include "../Texture.hpp"
#include "../systems/Camera.hpp"

class Tile
{
public:
    Tile();
    Tile(Texture *texture, SDL_Rect box);
    ~Tile();

    void render(Camera *camera);
    int getCenterX();
    int getCenterY();
    int getTextureId();
    SDL_Rect getBox();

private:
    Texture *texture;
    SDL_Rect box;
};

#endif