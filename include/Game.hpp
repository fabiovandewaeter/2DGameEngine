#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <time.h>
#include "systems/core/Camera.hpp"
#include "systems/core/TextureManager.hpp"
#include "systems/CollisionManager.hpp"
#include "systems/core/IOManager.hpp"
#include "systems/algorithms/PerlinNoise.hpp"
#include "systems/core/AudioManager.hpp"
#include "systems/core/TickManager.hpp"
#include "systems/game_objects/EntityManager.hpp"
#include "systems/game_objects/ItemFactory.hpp"
#include "systems/game_objects/StructureFactory.hpp"

struct TimeData
{
    Uint64 lastTime;
    Uint64 counter;
    Uint64 interval;
    Uint64 lastTimeLimiter;
    Uint64 counterLimiter;
};
class Texture;
class Player;
class MouseManager;
class GUIManager;
class Map;

class Game
{
public:
    Game(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, bool vsync, int UPS);
    ~Game();

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
    int screenWidth, screenHeight;
    unsigned int fixedFPS;
    unsigned int fixedUPS;
    Uint64 frameDelay;
    TickManager tickManager;
    SDL_Event event;

    // textures
    Texture *backgroundTexture;

    // musics
    std::vector<Mix_Music *> *musics;

    // game objects
    EntityManager entityManager;

    // systems
    TextureManager textureManager;
    IOManager ioManager;
    Map *map;
    PerlinNoise perlinNoise;
    AudioManager audioManager;
    ItemFactory itemFactory;
    GUIManager *guiManager;
    MouseManager *mouseManager;
    StructureFactory structureFactory;

    void loadMedia();
    void loadEntities();
    void loadItems();
    void countPrinter(std::string name, Uint64 &counter, Uint64 &interval, Uint64 &lastTime);
};

#endif
