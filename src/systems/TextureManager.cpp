#include "TextureManager.hpp"

TextureManager::TextureManager() {}
TextureManager::~TextureManager()
{
    free();
}
void TextureManager::free()
{
    for (int i = 0; i < NUMBER_OF_ENTITY_TEXTURES; i++)
    {
        this->entityTextures[i].free();
    }
    for (int i = 0; i < NUMBER_OF_TILE_TEXTURES; i++)
    {
        this->tileTextures[i].free();
    }
    this->backgroundTexture.free();
}

void TextureManager::loadMedia(SDL_Renderer *renderer)
{
    // background texture
    this->backgroundTexture.loadFromFile("assets/img/background.png", renderer);
    this->backgroundTexture.setSize(1280 * 5, 720 * 5);

    loadEntityTextures(renderer);
    loadTileTextures(renderer);
}

void TextureManager::loadEntityTextures(SDL_Renderer *renderer)
{
    int i = 0;
    // player texture
    this->entityTextures[i].loadFromFile("assets/img/player.png", renderer);
    i++;
    // entity0 texture
    this->entityTextures[i].loadFromFile("assets/img/entity0.png", renderer);
    i++;
}
void TextureManager::loadTileTextures(SDL_Renderer *renderer)
{
    int i = 0;
    // grass0 texture
    this->tileTextures[i].loadFromFile("assets/img/tiles/grass0.png", renderer);
    i++;
    // grass1 texture
    this->tileTextures[i].loadFromFile("assets/img/tiles/grass1.png", renderer);
    i++;
}

Texture *TextureManager::getBackgroundTexture()
{
    return &this->backgroundTexture;
}
Texture *TextureManager::getEntityTextures()
{
    return this->entityTextures;
}
Texture *TextureManager::getTileTextures()
{
    return this->tileTextures;
}