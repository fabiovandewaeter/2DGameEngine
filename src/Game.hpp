#ifndef game_hpp
#define game_hpp

#define NUMBER_OF_ENTITIES 1

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>

#include "Texture.hpp"
#include "entities/Player.hpp"
#include "systems/Camera.hpp"
#include "systems/CollisionManager.hpp"
#include "systems/IOManager.hpp"
#include "systems/TextureManager.hpp"
#include "map/Map.hpp"
#include "map/Tile.hpp"

class Game
{
public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void loadMedia();
    void loadEntities();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();
    void printFPS();
    void printUPS();
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
    Entity entities[NUMBER_OF_ENTITIES];
    Texture *backgroundTexture;
    Texture *entityTextures;
    Texture *tileTextures;
    Texture *staticObjectTextures;

    SDL_Surface *loadSurface(const char *path);
    SDL_Texture *loadTexture(const char *path);

    TextureManager textureManager;
    CollisionManager collisionManager;
    IOManager ioManager;
    Map map;
};

#endif