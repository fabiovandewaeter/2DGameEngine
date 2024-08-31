#include "Game.hpp"

LTexture backgroundTexture,playerTexture;
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
    frequency = SDL_GetPerformanceFrequency();
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    isRunning = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialised" << std::endl;
        // Create window
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window){std::cout << "Window created" << std::endl;}
        else {std::cout << "FAIL : Window NOT created" << std::endl; isRunning = false;};
        // Create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer){ SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); std::cout << "Renderer created" << std::endl;}
        else {std::cout << "FAIL : Renderer NOT created" << std::endl; isRunning = false;}
        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if ((IMG_Init(imgFlags) & imgFlags)) {std::cout << "SDL_image initialized" << std::endl;}
        else {std::cout << "FAIL : SDL_image NOT initialized" << std::endl; isRunning = false;}
    }

    loadMedia();
}

bool Game::loadMedia(){
    bool success = true;

    // Load background texture
    if (!backgroundTexture.loadFromFile("assets/img/background.png", renderer)){std::cout << "FAIL : background texture NOT loaded" << std::endl; success = false;}
    // Load player texture
    if (!playerTexture.loadFromFile("assets/img/player.png", renderer)){std::cout << "FAIL : player texture NOT loaded" << std::endl; success = false;}

    return success;
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
    t += 0.001;
    destR.h = x*t;
    destR.w = x*t;

    printUPS();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    backgroundTexture.render(0, 0, renderer);
    playerTexture.render(240, 190, renderer);

    SDL_RenderPresent(renderer);

    printFPS();
}

void Game::clean() {
    // Free loaded images
    playerTexture.free();
    backgroundTexture.free();

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running(){
    return isRunning;
}
void Game::setFPS(unsigned int fps){
    fixedFPS = fps;
}
void Game::setUPS(unsigned int ups){
    fixedUPS = ups;
    frameDelay = frequency / fixedUPS;
}