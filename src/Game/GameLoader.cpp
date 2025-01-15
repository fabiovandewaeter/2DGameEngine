#include "game/GameLoader.hpp"

#include "entities/Player.hpp"

GameLoader::GameLoader() {}
GameLoader::~GameLoader() {}

void init(TextureManager *textureManager, std::vector<Texture *> *entityTextures, std::vector<Texture *> *tileTextures, std::vector<Texture *> *passiveStructureTextures, std::vector<Texture *> *activeStructureTextures){
}

void GameLoader::loadMedia(TextureManager*textureManager)
{
    // textures
    textureManager.init(renderer);
    textureManager.loadMedia();
    backgroundTexture = textureManager.getBackgroundTexture();
    entityTextures = textureManager.getEntityTextures();
    tileTextures = textureManager.getTileTextures();
    passiveStructureTextures = textureManager.getPassiveStructureTextures();
    activeStructureTextures = textureManager.getActiveStructureTextures();

    // audio
    audioManager.init();
    audioManager.loadMedia();
    music = audioManager.getMusic();
}
Player *GameLoader::loadEntities()
{
    entityManager.loadEntities();
    Player *player = new Player((*entityTextures)[0], (SDL_Rect){0, 0, 16, 16}, 100);
    entityManager.addEntity(player);
    return player;
}
void GameLoader::loadItems()
{
    itemManager.load();
}
