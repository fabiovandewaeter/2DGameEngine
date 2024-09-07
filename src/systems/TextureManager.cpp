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
    // player texture
    this->entityTextures[0].loadFromFile("assets/img/player.png", renderer);
    // entity0 texture
    this->entityTextures[1].loadFromFile("assets/img/entity0.png", renderer);
}
void TextureManager::loadTileTextures(SDL_Renderer *renderer)
{
    // ground texture
    this->tileTextures[0].loadFromFile("assets/img/ground.png", renderer);
    // grass0 texture
    this->tileTextures[1].loadFromFile("assets/img/tiles/grass0.png", renderer);
    // grass1 texture
    this->tileTextures[2].loadFromFile("assets/img/tiles/grass1.png", renderer);
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