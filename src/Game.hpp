#ifndef game_hpp
#define game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>

class Game {
public:
    unsigned int fixedFPS = 60;
    unsigned int fixedUPS = 60;
    Uint64 frameDelay, frequency;
    

    Game();
    ~Game();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();
    void printFPS();
    void printUPS();
    void changeFPS(unsigned int fps);
    void changeUPS(unsigned int ups);

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    SDL_Surface *loadSurface(const char *path);
};

#endif