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
    if (!this->backgroundTexture.loadFromFile("assets/img/background.png", renderer))
    {
        std::cout << "FAIL : background texture NOT loaded" << std::endl;
    }
    this->backgroundTexture.setSize(1280 * 5, 720 * 5);

    loadEntityTextures(renderer);
    loadTileTextures(renderer);
}

void TextureManager::loadEntityTextures(SDL_Renderer *renderer)
{
    // player texture
    if (!this->entityTextures[0].loadFromFile("assets/img/player.png", renderer))
    {
        std::cout << "FAIL : player texture NOT loaded" << std::endl;
    }
    // entity0 texture
    if (!this->entityTextures[1].loadFromFile("assets/img/entity0.png", renderer))
    {
        std::cout << "FAIL : texture[2] NOT loaded" << std::endl;
    }
}
void TextureManager::loadTileTextures(SDL_Renderer *renderer)
{
    // ground texture
    if (!this->tileTextures[0].loadFromFile("assets/img/ground.png", renderer))
    {
        std::cout << "FAIL : ground texture NOT loaded" << std::endl;
    }
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