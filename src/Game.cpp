#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "Game.hpp"

#include "systems/core/MouseManager.hpp"
#include "systems/core/GUIManager.hpp"
#include "structures/activeStructures/Core.hpp"
#include "structures/activeStructures/Turret.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "map/Tile.hpp"
#include "entities/Player.hpp"
#include "Texture.hpp"

Game::Game(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, bool vsync)
{
    this->fixedFPS = 60;
    this->fixedUPS = 60;
    this->screenWidth = width;
    this->screenHeight = height;
    // initialize window
    int flags = 0;
    if (fullscreen)
    {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }
    if (vsync)
    {
        flags = flags | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    }
    this->running = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised" << std::endl;
        // Create window
        if (!(this->window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags)))
        {
            std::cout << "FAIL : Window NOT created" << std::endl;
            running = false;
        }
        // Create renderer
        if ((this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED)))
        {
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        else
        {
            std::cout << "FAIL : Renderer NOT created" << std::endl;
            running = false;
        }
        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "FAIL : SDL_image NOT initialized" << std::endl;
            running = false;
        }
        // Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            running = false;
        }
        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            running = false;
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

    loadMedia();
    std::cout << "================= new Map() =================" << std::endl;
    this->map = new Map(Tile::getTileSize(), &this->textureManager, &this->perlinNoise);
    loadEntities();
    std::cout << "================= itemFactory.init() =================" << std::endl;
    this->itemFactory.init();
    loadItems();

    this->structureFactory = StructureFactory::getInstance();
    std::vector<std::string> a = this->structureFactory.getRegistredClasses();
    std::cout << "================= new MouseManager() =================" << std::endl;
    this->mouseManager = new MouseManager();
    std::cout << "================= new GUIManager() =================" << std::endl;
    this->guiManager = new GUIManager(this->window, this->renderer, &this->textureManager, &this->tickManager, &this->structureFactory, this->mouseManager);
}
Game::~Game()
{
}

void Game::run()
{
    while (this->isRunning())
    {
        tickManager.setFrameStart();
        handleEvents();
        update();
        render();
        tickManager.waitTick(getFrameDelay());
#ifdef PROFILER
        FrameMark;
#endif
    }
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&this->event) != 0)
    {
        if (this->event.type == SDL_QUIT)
        {
            this->running = false;
        }
        this->player->handleEvents(&this->event, this->guiManager, this->mouseManager);
    }
}

TimeData timeData = {SDL_GetTicks64(), 0, 1000, SDL_GetTicks64(), 0};
void Game::update()
{
    // if (limiter("UPS", timeData.counterLimiter, 1000 / this->fixedUPS, timeData.lastTimeLimiter))
    this->player->update();
    this->map->update();

    countPrinter("UPS", timeData.counter, timeData.interval, timeData.lastTime);
}

TimeData timeData2 = {SDL_GetTicks64(), 0, 1000, SDL_GetTicks64(), 0};
void Game::render()
{
    // if (limiter("FPS", timeData2.counterLimiter, 1000 / this->fixedFPS, timeData2.lastTimeLimiter))
    SDL_RenderClear(this->renderer);

    this->backgroundTexture->render((int)((this->screenWidth / 2) - (this->backgroundTexture->getCenterX())), (int)((this->screenHeight / 2) - (this->backgroundTexture->getCenterY())), (int)(this->backgroundTexture->getWidth()), (int)(this->backgroundTexture->getHeight()));
    this->player->render();
    this->guiManager->render(this->player);

    SDL_RenderPresent(this->renderer);
    countPrinter("FPS", timeData2.counter, timeData2.interval, timeData2.lastTime);
}

void Game::clean()
{
    delete this->map;
    this->audioManager.free();

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::isRunning() { return this->running; }
void Game::setFPS(unsigned int fps) { this->fixedFPS = fps; }
void Game::setUPS(unsigned int ups)
{
    this->fixedUPS = ups;
    this->frameDelay = 10000000 / this->fixedUPS;
}
Uint64 Game::getFrameDelay() { return this->frameDelay; }
SDL_Window *Game::getWindow() { return this->window; }
SDL_Renderer *Game::getRenderer() { return this->renderer; }
void Game::countPrinter(std::string name, Uint64 &counter, Uint64 &interval, Uint64 &lastTime)
{
    counter++;
    Uint64 currentTime = SDL_GetTicks64();
    Uint64 deltaTime = currentTime - lastTime;
    if (deltaTime >= interval)
    { // 1000 ms = 1 seconde
        std::cout << name << ": " << std::fixed << counter / (deltaTime / 1000.0f) << std::endl;
        lastTime = currentTime;
        counter = 0;
    }
}
void Game::loadMedia()
{
    std::cout << "================= Game::LoadMedia() =================" << std::endl;
    // textures
    this->textureManager.init(this->renderer);
    this->backgroundTexture = this->textureManager.getTexture("BACKGROUND");

    // audio
    this->audioManager.init();
    this->audioManager.loadMedia();
    this->musics = this->audioManager.getMusic();
}
#include "entities/behaviors/WarriorBehavior.hpp"
#include "entities/behaviors/ExplorerBehavior.hpp"
void Game::loadEntities()
{
    std::cout << "================= Game::LoadEntities() =================" << std::endl;
    this->player = new Player(this->textureManager.getTexture("Player"), (SDL_Rect){0, 0, 16, 16}, 100, this->map, new Camera(this->screenWidth, this->screenHeight, 10, 20000, 0, 0));
    this->map->addEntity(this->player);

    // test
    //this->map->addEntity(new Entity(this->textureManager.getTexture("Warrior"), (SDL_Rect){0, 0, 16, 16}, 100, new WarriorBehavior()));
    //this->map->addEntity(new Entity(this->textureManager.getTexture("Explorer"), (SDL_Rect){0, 0, 16, 16}, 100, new ExplorerBehavior()));
}
void Game::loadItems()
{
    std::cout << "================= Game::LoadItems() =================" << std::endl;
    this->itemFactory.load();
}
