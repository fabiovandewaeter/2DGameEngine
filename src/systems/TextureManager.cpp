#include "TextureManager.hpp"

TextureManager::TextureManager(){}
TextureManager::TextureManager(SDL_Renderer *renderer)
{
    init(renderer);
}
TextureManager::~TextureManager()
{
    free();
}
void TextureManager::free()
{
    this->backgroundTexture->free();
    int size = this->entityTextures.size();
    for (int i = 0; i < size; i++)
    {
        this->entityTextures[i]->free();
    }
    size = this->tileTextures.size();
    for (int i = 0; i < size; i++)
    {
        this->tileTextures[i]->free();
    }
    size = this->staticObjectTextures.size();
    for (int i = 0; i < size; i++)
    {
        this->staticObjectTextures[i]->free();
    }
}

void TextureManager::init(SDL_Renderer *renderer){
    this->renderer = renderer;
}
void TextureManager::loadMedia()
{
    // background texture
    this->backgroundTexture = (new Texture(this->renderer))->loadFromFile("assets/img/background.png");
    this->backgroundTexture->setSize(1280 * 5, 720 * 5);

    loadEntityTextures();
    loadTileTextures();
    loadStaticObjectTextures();
}

void TextureManager::loadEntityTextures()
{
    this->entityTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/player.png"));
    this->entityTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/entity0.png"));
}
void TextureManager::loadTileTextures()
{
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass0.png"));
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass1.png"));
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass2.png"));
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass3.png"));
}
void TextureManager::loadStaticObjectTextures()
{
    this->staticObjectTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/objects/staticObjects/wall_stone.png"));
    this->staticObjectTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/objects/staticObjects/wall_wood.png"));
    this->staticObjectTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/objects/staticObjects/door_wood.png"));
}

Texture *TextureManager::getBackgroundTexture()
{
    return this->backgroundTexture;
}
std::vector<Texture *> *TextureManager::getEntityTextures()
{
    return &this->entityTextures;
}
std::vector<Texture *> *TextureManager::getTileTextures()
{
    return &this->tileTextures;
}
std::vector<Texture *> *TextureManager::getStaticObjectTextures()
{
    return &this->staticObjectTextures;
}