#ifndef game_hpp
#define game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>

class Game {
public:
    unsigned int fixedFPS = 90;
    unsigned int fixedUPS = 60;
    void printFPS();
    void printUPS();

    Game();
    ~Game();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    SDL_Surface *loadSurface(const char *path);
};

#endif