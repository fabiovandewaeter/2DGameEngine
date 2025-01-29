#include "systems/core/TextureManager.hpp"

#include "Texture.hpp"

TextureManager::TextureManager() {}
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
    int size = this->textures.size();
    for (int i = 0; i < size; i++)
    {
        this->textures[i]->free();
    }
}

void TextureManager::init(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}
void loadConfiguration(){
    READ ./data/configurations/TextureManagerConfiguration.json AND FILL this->textures THEN PASS TextureManager TO ALL CLASSES MAIS USE IT TO GET TEXTURE OF STRUCTURES IN GUIManager
}
void TextureManager::loadMedia()
{
    // background texture
    this->backgroundTexture = (new Texture(this->renderer))->loadFromFile("assets/img/background.png");
    this->backgroundTexture->setSize(1280 * 5, 720 * 5);

    loadEntityTextures();
    loadTileTextures();
    loadPassiveStructureTextures();
    loadActiveStructureTextures();
    loadGUITextures();
}

void TextureManager::loadEntityTextures()
{
    // player
    this->entityTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/player.png"));
    // entities
    this->entityTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/entity0.png"));
}
void TextureManager::loadTileTextures()
{
    // grass
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass0.png"));
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass1.png"));
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass2.png"));
    this->tileTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/tiles/grass3.png"));
}
void TextureManager::loadPassiveStructureTextures()
{
    // walls
    this->passiveStructureTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/structures/passiveStructures/wall_stone.png"));
    this->passiveStructureTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/structures/passiveStructures/wall_wood.png"));
    // doors
    this->passiveStructureTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/structures/passiveStructures/door_wood.png"));
}
void TextureManager::loadActiveStructureTextures()
{
    // core
    this->activeStructureTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/structures/activeStructures/core.png"));
    // turret
    this->activeStructureTextures.push_back((new Texture(this->renderer))->loadFromFile("assets/img/structures/activeStructures/turret.png"));
}
void TextureManager::loadGUITextures()
{
    this->GUITextures.push_back((new Texture(this->renderer))->loadFromFile("assets/icon/GUI/greater-than.png"));
    this->GUITextures.push_back((new Texture(this->renderer))->loadFromFile("assets/icon/GUI/down.png"));
}

Texture *TextureManager::getBackgroundTexture() { return this->backgroundTexture; }
std::vector<Texture *> *TextureManager::getEntityTextures() { return &this->entityTextures; }
std::vector<Texture *> *TextureManager::getTileTextures() { return &this->tileTextures; }
std::vector<Texture *> *TextureManager::getPassiveStructureTextures() { return &this->passiveStructureTextures; }
std::vector<Texture *> *TextureManager::getActiveStructureTextures() { return &this->activeStructureTextures; }
std::vector<Texture *> *TextureManager::getGUITextures() { return &this->GUITextures; }
