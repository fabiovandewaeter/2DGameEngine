#ifndef game_hpp
#define game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>

#include "Texture.hpp"
#include "entities/Player.hpp"
#include "systems/Camera.hpp"
#include "systems/CollisionManager.hpp"
#include "systems/IOManager.hpp"
#include "systems/TextManager.hpp"
#include "systems/TextureManager.hpp"
#include "systems/PerlinNoise.hpp"
#include "systems/MouseManager.hpp"
#include "systems/EntityManager.hpp"
#include "map/Map.hpp"
#include "map/Tile.hpp"
#include "structures/Structure.hpp"
#include "structures/activeStructures/Core.hpp"

class Game
{
public:
    Game();
    ~Game();

    void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen);
    void loadMedia();
    void loadEntities();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();
    bool limiter(std::string name, Uint64 &counter, Uint64 interval, Uint64 &lastTime);
    void countPrinter(std::string name, Uint64 &counter, Uint64 interval, Uint64 &lastTime);
    void setFPS(unsigned int fps);
    void setUPS(unsigned int ups);
    Uint64 getFrameDelay();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera camera;
    int screenWidth, screenHeight;
    unsigned int fixedFPS;
    unsigned int fixedUPS;
    Uint64 frameDelay;

    Player player;
    Texture *backgroundTexture;
    std::vector<Texture *> *entityTextures;
    std::vector<Texture *> *tileTextures;
    std::vector<Texture *> *passiveStructureTextures;
    std::vector<Texture *> *activeStructureTextures;

    TextManager textManager;
    TextureManager textureManager;
    CollisionManager collisionManager;
    IOManager ioManager;
    Map map;
    PerlinNoise perlinNoise;
    MouseManager mouseManager;
    EntityManager entityManager;

    SDL_Surface *loadSurface(std::string path);
    SDL_Texture *loadTexture(std::string path);
};

#endif
