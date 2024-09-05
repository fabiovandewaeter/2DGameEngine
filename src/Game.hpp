#ifndef game_hpp
#define game_hpp

#define NUMBER_OF_TEXTURES 3
#define NUMBER_OF_ENTITIES 1

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>

#include "LTexture.hpp"
#include "entities/Player.hpp"

class Game {
public:
    Game();
    ~Game();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    bool loadMedia();
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
    unsigned int fixedFPS;
    unsigned int fixedUPS;
    Uint64 frameDelay;
    LTexture textures[NUMBER_OF_TEXTURES];
    
    Player player;
    Entity entities[NUMBER_OF_ENTITIES];
    
    SDL_Surface *loadSurface(const char *path);
    SDL_Texture *loadTexture(const char *path);
};

#endif