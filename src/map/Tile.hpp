#ifndef tile_hpp
#define tile_hpp

#include "../Texture.hpp"

class Tile
{
public:
    Tile(Texture *texture, SDL_Rect box);
    ~Tile();

    void render(SDL_Renderer *renderer, int cameraCenterX, int cameraCenterY, int cameraPositionX, int cameraPositionY, double scale);
    int getCenterX();
    int getCenterY();
    int getTextureId();

private:
    Texture *texture;
    SDL_Rect box;
};

#endif