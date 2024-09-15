#ifndef texture_manager_hpp
#define texture_manager_hpp

#include <vector>
#include "../Texture.hpp"

class TextureManager
{
public:
    TextureManager();
    TextureManager(SDL_Renderer *renderer);
    ~TextureManager();
    void free();

    void init(SDL_Renderer *renderer);
    void loadMedia();
    void loadEntityTextures();
    void loadTileTextures();
    void loadStaticObjectTextures();
    void loadStructureTextures();

    Texture *getBackgroundTexture();
    std::vector<Texture *> *getEntityTextures();
    std::vector<Texture *> *getTileTextures();
    std::vector<Texture *> *getStaticObjectTextures();
    std::vector<Texture *> *getStructureTextures();

private:
    SDL_Renderer *renderer;
    Texture *backgroundTexture;
    std::vector<Texture *> entityTextures;
    std::vector<Texture *> tileTextures;
    std::vector<Texture *> staticObjectTextures;
    std::vector<Texture *> structureTextures;
};

#endif