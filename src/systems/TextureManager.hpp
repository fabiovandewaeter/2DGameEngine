#ifndef texture_manager_hpp
#define texture_manager_hpp

#define NUMBER_OF_ENTITY_TEXTURES 2
#define NUMBER_OF_ENTITIES 2
#define NUMBER_OF_TILE_TEXTURES 3

#include "../Texture.hpp"

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    void free();

    void loadMedia(SDL_Renderer *renderer);
    void loadEntityTextures(SDL_Renderer *renderer);
    void loadTileTextures(SDL_Renderer *renderer);

    Texture *getBackgroundTexture();
    Texture *getEntityTextures();
    Texture *getTileTextures();
private:
    Texture backgroundTexture;
    Texture entityTextures[NUMBER_OF_ENTITY_TEXTURES];
    Texture tileTextures[NUMBER_OF_TILE_TEXTURES];
};

#endif