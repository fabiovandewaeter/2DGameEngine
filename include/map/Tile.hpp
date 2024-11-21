#ifndef tile_hpp
#define tile_hpp

#define TILE_SIZE 16

#include <SDL2/SDL_rect.h>
#include <vector>

class Texture;
class Camera;

class Tile
{
public:
    Tile(Texture *texture, int x, int y);
    ~Tile();

    void render(Camera *camera);
    int getCenterX();
    int getCenterY();
    int getTextureId();
    static int getTileSize();

private:
    Texture *texture;
    int x, y;
};

#endif