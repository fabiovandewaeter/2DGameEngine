#ifndef game_hpp
#define game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>

#include "LTexture.hpp"

class Game {
public:
    unsigned int fixedFPS = 60;
    unsigned int fixedUPS = 60;
    Uint64 frameDelay;
    

    Game();
    ~Game();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    bool loadMedia();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();
    void printFPS();
    void printUPS();
    void setFPS(unsigned int fps);
    void setUPS(unsigned int ups);

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    SDL_Surface *loadSurface(const char *path);
    SDL_Texture *loadTexture(const char *path);
};

#endif