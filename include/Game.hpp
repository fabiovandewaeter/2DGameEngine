#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <time.h>
#include "map/Map.hpp"
#include "systems/Camera.hpp"
#include "systems/TextManager.hpp"
#include "systems/TextureManager.hpp"
#include "systems/CollisionManager.hpp"
#include "systems/IOManager.hpp"
#include "systems/PerlinNoise.hpp"
#include "systems/MouseManager.hpp"
#include "systems/EntityManager.hpp"
#include "systems/AudioManager.hpp"
#include "systems/ItemManager.hpp"
#include "systems/GUIManager.hpp"
#include "systems/TickManager.hpp"

struct TimeData
{
    Uint64 lastTime;
    Uint64 counter;
    Uint64 interval;
    Uint64 lastTimeLimiter;
    Uint64 counterLimiter;
};
class Texture;
class Core;
class Turret;
class Player;

class Game
{
public:
    Game();
    ~Game();

    void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, bool vsync);
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning();
    void setFPS(unsigned int fps);
    void setUPS(unsigned int ups);
    Uint64 getFrameDelay();
    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera camera;
    int screenWidth, screenHeight;
    unsigned int fixedFPS;
    unsigned int fixedUPS;
    Uint64 frameDelay;
    TickManager tickManager;

    Player *player;
    Texture *backgroundTexture;
    std::vector<Texture *> *entityTextures;
    std::vector<Texture *> *tileTextures;
    std::vector<Texture *> *passiveStructureTextures;
    std::vector<Texture *> *activeStructureTextures;

    std::vector<Mix_Music *> *music;

    Core *core;
    Turret *turret;

    TextManager textManager;
    TextureManager textureManager;
    CollisionManager collisionManager;
    IOManager ioManager;
    Map map;
    PerlinNoise perlinNoise;
    MouseManager mouseManager;
    EntityManager entityManager;
    AudioManager audioManager;
    ItemManager itemManager;
    GUIManager guiManager;


    void loadMedia();
    void loadEntities();
    void loadItems();
    void countPrinter(std::string name, Uint64 &counter, Uint64 &interval, Uint64 &lastTime);
};

#endif
