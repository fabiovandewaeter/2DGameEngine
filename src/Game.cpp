#include "Game.hpp"

Player player;
SDL_Rect srcR, destR;

SDL_Event event;

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
    this->fixedFPS = 60;
    this->fixedUPS = 60;

    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    this->isRunning = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialised" << std::endl;
        // Create window
        this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window){std::cout << "Window created" << std::endl;}
        else {std::cout << "FAIL : Window NOT created" << std::endl; isRunning = false;};
        // Create renderer
        this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer){ SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); std::cout << "Renderer created" << std::endl;}
        else {std::cout << "FAIL : Renderer NOT created" << std::endl; isRunning = false;}
        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if ((IMG_Init(imgFlags) & imgFlags)) {std::cout << "SDL_image initialized" << std::endl;}
        else {std::cout << "FAIL : SDL_image NOT initialized" << std::endl; isRunning = false;}
    }

    loadMedia();
    destR.h = 16;
    destR.w = 16;
    
    SDL_Rect r = {10, 10, 20, 20};
    player.init(textures[1], r);
    player.setVelocity(0, 0);
}

bool Game::loadMedia(){
    bool success = true;

    // Load background texture
    if (!textures[0].loadFromFile("assets/img/background.png", renderer)){std::cout << "FAIL : background texture NOT loaded" << std::endl; success = false;}
    // Load player texture
    if (!textures[1].loadFromFile("assets/img/player.png", renderer)){std::cout << "FAIL : player texture NOT loaded" << std::endl; success = false;}

    return success;
}

// source : https://lazyfoo.net/tutorials/SDL/18_key_states/index.php
void Game::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            this->isRunning = false;
        }
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_DOWN]){
        }
    }
}

void Game::update() {
    player.update();

    printUPS();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    textures[0].render(0, 0, renderer);
    //textures[1].render(10, 10, renderer);
    player.render(renderer);

    SDL_RenderPresent(renderer);

    printFPS();
}

void Game::clean() {
    // Free loaded images
    for (int i = 0; i < NUMBER_OF_TEXTURES; i++){
        textures[i].free();
    }

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running(){
    return this->isRunning;
}
void Game::setFPS(unsigned int fps){
    this->fixedFPS = fps;
}
void Game::setUPS(unsigned int ups){
    this->fixedUPS = ups;
    this->frameDelay = 10000000 / this->fixedUPS;
}
Uint64 Game::getFrameDelay(){
    return this->frameDelay;
}