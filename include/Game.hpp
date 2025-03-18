#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <time.h>

#include "systems/core/Camera.hpp"
#include "systems/core/TextureManager.hpp"
#include "systems/algorithms/PerlinNoise.hpp"
#include "systems/core/AudioManager.hpp"
#include "systems/core/TickManager.hpp"
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
class EntityManager;
class GUIManager;
class Map;

class Game
{
public:
    Game(std::string title, int windowWidth, int windowHeight, bool fullscreen, bool vsync, int UPS);
    ~Game();

    void run();
    void handleEvents();
    void update();
    void render();

    bool isRunning();
    void setFPS(unsigned int fps);
    void setUPS(unsigned int ups);
    Uint64 getFrameDelay();

private:
    std::string title;
    int windowWidth, windowHeight;
    bool running;
    unsigned int FPS;
    unsigned int UPS;
    Uint64 frameDelay;
    TickManager tickManager;
    SDL_Event event;
    int flags;

    // musics
    std::vector<Mix_Music *> *musics;

    // systems
    Map *map;
    PerlinNoise perlinNoise;
    AudioManager audioManager;
    ItemFactory itemFactory;
    StructureFactory structureFactory;

    void loadMedia();
    void loadEntities();
    void loadItems();
    void countPrinter(std::string name, Uint64 &counter, Uint64 &interval, Uint64 &lastTime);
};

#endif
