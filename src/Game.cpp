#include "Game.hpp"

#include <thread>
#include <chrono>

SDL_Texture *playerTex;
SDL_Rect srcR, destR;

unsigned int frameCount = 0, updateCount = 0;
float fps = 0, ups = 0;
Uint64 lastTimeFPS = SDL_GetTicks64(), currentTimeFPS, lastTimeUPS = lastTimeFPS, currentTimeUPS;
void Game::printFPS(){
    frameCount++;
    currentTimeFPS = SDL_GetTicks64();
    if (currentTimeFPS- lastTimeFPS >= 1000) { // 1000 ms = 1 seconde
        fps = frameCount / ((currentTimeFPS - lastTimeFPS) / 1000.0f);
        std::cout << "FPS: " << fps << std::endl;
        lastTimeFPS = currentTimeFPS;
        frameCount = 0;
    }
}
void Game::printUPS(){
    updateCount++;
    currentTimeUPS = SDL_GetTicks64();
    if (currentTimeUPS - lastTimeUPS >= 1000) { // 1000 ms = 1 seconde
        ups = updateCount / ((currentTimeUPS - lastTimeUPS) / 1000.0f);
        std::cout << "UPS: " << ups << std::endl;
        lastTimeUPS = currentTimeUPS;
        updateCount = 0;
    }
}

Game::Game()
{
}
Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialised" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window){
            std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    }
    else {
        isRunning = false;
    }

    // load player texture
    SDL_Surface *tmpSurface = IMG_Load("src/assets/img/player.png");
    playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT){
        isRunning = false;
    }

}

int x = 16;
double t = 1;
void Game::update() {
    printUPS();
    t += 0.001;
    destR.h = x*t;
    destR.w = x*t;
}

void Game::render() {
    printFPS();

    SDL_RenderClear(renderer);

    // this is where we would add stuff to render
    // render player texture
    SDL_RenderCopy(renderer, playerTex, NULL, &destR);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running(){
    return isRunning;
}