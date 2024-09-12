#include "TextureManager.hpp"

TextureManager::TextureManager() {}
TextureManager::~TextureManager()
{
    free();
}
void TextureManager::free()
{
    this->backgroundTexture.free();
    for (int i = 0; i < NUMBER_OF_ENTITY_TEXTURES; i++)
    {
        this->entityTextures[i].free();
    }
    for (int i = 0; i < NUMBER_OF_TILE_TEXTURES; i++)
    {
        this->tileTextures[i].free();
    }
    for (int i = 0; i < NUMBER_OF_STATIC_OBJECT_TEXTURES; i++)
    {
        this->staticObjectTextures[i].free();
    }
}

void TextureManager::loadMedia(SDL_Renderer *renderer)
{
    // background texture
    this->backgroundTexture.loadFromFile("assets/img/background.png", renderer);
    this->backgroundTexture.setSize(1280 * 5, 720 * 5);

    loadEntityTextures(renderer);
    loadTileTextures(renderer);
    loadStaticObjectTextures(renderer);
}

void TextureManager::loadEntityTextures(SDL_Renderer *renderer)
{
    int i = 0;
    this->entityTextures[i].loadFromFile("assets/img/player.png", renderer);
    i++;
    this->entityTextures[i].loadFromFile("assets/img/entity0.png", renderer);
    i++;
}
void TextureManager::loadTileTextures(SDL_Renderer *renderer)
{
    int i = 0;
    this->tileTextures[i].loadFromFile("assets/img/tiles/grass0.png", renderer);
    i++;
    this->tileTextures[i].loadFromFile("assets/img/tiles/grass1.png", renderer);
    i++;
    this->tileTextures[i].loadFromFile("assets/img/tiles/grass2.png", renderer);
    i++;
    this->tileTextures[i].loadFromFile("assets/img/tiles/grass3.png", renderer);
    i++;
}
void TextureManager::loadStaticObjectTextures(SDL_Renderer *renderer)
{
    int i = 0;
    this->staticObjectTextures[i].loadFromFile("assets/img/objects/staticObjects/wall_stone.png", renderer);
    i++;
    this->staticObjectTextures[i].loadFromFile("assets/img/objects/staticObjects/wall_wood.png", renderer);
    i++;
    this->staticObjectTextures[i].loadFromFile("assets/img/objects/staticObjects/door_wood.png", renderer);
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
Texture *TextureManager::getStaticObjectTextures()
{
    return this->staticObjectTextures;
}