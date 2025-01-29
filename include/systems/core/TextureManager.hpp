#ifndef texture_manager_hpp
#define texture_manager_hpp

#include <SDL2/SDL.h>
#include <unordered_map>

class Texture;

class TextureManager
{
public:
    TextureManager();
    TextureManager(SDL_Renderer *renderer);
    ~TextureManager();
    void free();

    void init(SDL_Renderer *renderer);
    void loadConfiguration();
    void loadMedia();
    Texture *getTextures(std::string className);

    Texture *getBackgroundTexture();

private:
    SDL_Renderer *renderer;
    Texture *backgroundTexture;
    std::unordered_map<std::string, Texture *> textures;
};

#endif
