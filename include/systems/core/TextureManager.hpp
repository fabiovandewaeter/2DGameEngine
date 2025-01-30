#ifndef texture_manager_hpp
#define texture_manager_hpp

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <string>

class Texture;

class TextureManager
{
public:
    TextureManager();
    TextureManager(SDL_Renderer *renderer);
    ~TextureManager();

    void init(SDL_Renderer *renderer);
    void loadConfiguration();
    Texture *getTexture(std::string name);

private:
    SDL_Renderer *renderer;
    std::unordered_map<std::string, Texture *> textures;
};

#endif
