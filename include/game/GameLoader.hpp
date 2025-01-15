#ifndef game_loader_hpp
#define game_loader_hpp

#include <vector>

#include "systems/JSONManager.hpp"

class TextureManager;
class Texture;
class Player;

class GameLoader
{
public:
    GameLoader();
    ~GameLoader();

    void init(TextureManager *textureManager, std::vector<Texture *> *entityTextures, std::vector<Texture *> *tileTextures, std::vector<Texture *> *passiveStructureTextures, std::vector<Texture *> *activeStructureTextures);
    void loadMedia();
    Player *loadEntities();
    void loadItems();

private:
    JSONManager jsonManager;
};

#endif
