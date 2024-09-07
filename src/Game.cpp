#include "Game.hpp"

SDL_Rect srcR, destR;

SDL_Event event;

unsigned int frameCount = 0, updateCount = 0;
float fps = 0, ups = 0;
Uint64 lastTimeFPS = SDL_GetTicks64(), currentTimeFPS, lastTimeUPS = lastTimeFPS, currentTimeUPS;
void Game::printFPS()
{
    frameCount++;
    currentTimeFPS = SDL_GetTicks64();
    if (currentTimeFPS - lastTimeFPS >= 1000)
    { // 1000 ms = 1 seconde
        fps = frameCount / ((currentTimeFPS - lastTimeFPS) / 1000.0f);
        std::cout << "FPS: " << fps << std::endl;
        lastTimeFPS = currentTimeFPS;
        frameCount = 0;
    }
}
void Game::printUPS()
{
    updateCount++;
    currentTimeUPS = SDL_GetTicks64();
    if (currentTimeUPS - lastTimeUPS >= 1000)
    { // 1000 ms = 1 seconde
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
    this->screenWidth = width;
    this->screenHeight = height;

    // initialize window
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    this->isRunning = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised" << std::endl;
        // Create window
        this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (this->window)
        {
            std::cout << "Window created" << std::endl;
        }
        else
        {
            std::cout << "FAIL : Window NOT created" << std::endl;
            isRunning = false;
        };
        // Create renderer
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
        if (this->renderer)
        {
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        else
        {
            std::cout << "FAIL : Renderer NOT created" << std::endl;
            isRunning = false;
        }
        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if ((IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "SDL_image initialized" << std::endl;
        }
        else
        {
            std::cout << "FAIL : SDL_image NOT initialized" << std::endl;
            isRunning = false;
        }
    }
    // window icon
    SDL_Surface *iconSurface = SDL_LoadBMP("assets/icon/window_icon.bmp");
    if (!iconSurface)
    {
        std::cout << "Failed to load icon: " << IMG_GetError() << std::endl;
    }
    SDL_SetWindowIcon(this->window, iconSurface);
    SDL_FreeSurface(iconSurface);

    this->textureManager.loadMedia(this->renderer);
    this->backgroundTexture = this->textureManager.getBackgroundTexture();
    this->entityTextures = this->textureManager.getEntityTextures();
    this->tileTextures = this->textureManager.getTileTextures();
    loadEntities();
    this->camera.init(width, height, 2.0, 2.0, 0, 0);
}

void Game::loadMedia()
{
    this->textureManager.loadMedia(this->renderer);
}

void Game::loadEntities(){
    // ground
    this->entities[0].init(&this->tileTextures[0], (SDL_Rect){0, 0, 500, 500}, false);
    // player
    this->player.init(&this->entityTextures[0], (SDL_Rect){0, 0, 16, 16}, false);
    // entity0
    this->entities[1].init(&this->entityTextures[1], (SDL_Rect){50, 50, 16, 16}, true);
    
    this->collisionManager.addEntity(&this->player);
    for (int i = 1; i < NUMBER_OF_ENTITIES; i++){
        this->collisionManager.addEntity(&this->entities[i]);
    }
}

void Game::handleEvents(){
    while (SDL_PollEvent(&event) != 0)
    {
        int velocityX = 0;
        int velocityY = 0;

        if (event.type == SDL_QUIT)
        {
            this->isRunning = false;
        }

        this->camera.handleEvents(&event);
        this->player.handleEvents(&event);
    }
}

void Game::update()
{
    this->player.update(&this->collisionManager);
    this->camera.update();
    for (int i = 0; i < NUMBER_OF_ENTITIES; i++){
        this->entities[i].update(&this->collisionManager);
    }
    printUPS();
}

void Game::render()
{
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    int cameraPositionX = this->camera.getPositionX();
    int cameraPositionY = this->camera.getPositionY();
    int cameraCenterX = (this->screenWidth / 2);
    int cameraCenterY = (this->screenHeight/ 2);
    double scale = this->camera.getScale();
    // background
    this->backgroundTexture->render(this->renderer, cameraCenterX - (this->backgroundTexture->getCenterX() * scale), cameraCenterY - (this->backgroundTexture->getCenterY() * scale), scale);
    for (int i = 0; i < NUMBER_OF_ENTITIES; i++){
        this->entities[i].render(this->renderer, cameraCenterX, cameraCenterY, cameraPositionX, cameraPositionY, scale);
    }
    this->player.render(this->renderer, cameraCenterX, cameraCenterY, cameraPositionX, cameraPositionY, scale);

    SDL_RenderPresent(this->renderer);
    //printFPS();
}

void Game::clean()
{
    this->textureManager.free();

    // Destroy window
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running()
{
    return this->isRunning;
}
void Game::setFPS(unsigned int fps)
{
    this->fixedFPS = fps;
}
void Game::setUPS(unsigned int ups)
{
    this->fixedUPS = ups;
    this->frameDelay = 10000000 / this->fixedUPS;
}
Uint64 Game::getFrameDelay()
{
    return this->frameDelay;
}