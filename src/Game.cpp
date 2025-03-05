#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "Game.hpp"

#include "map/Map.hpp"
#include "entities/Player.hpp"

Game::Game(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, bool vsync, int UPS)
{
    this->title = title;
    std::cout << "\n======================================================" << std::endl;
    this->fixedFPS = 60;
    this->fixedUPS = 60;
    this->screenWidth = width;
    this->screenHeight = height;
    setUPS(UPS);
    std::cout << "Window width: " << width << std::endl;
    std::cout << "Window height: " << height << std::endl;
    std::cout << "UPS: " << UPS << std::endl;
    std::cout << "vsync: " << (vsync ? "true" : "false") << std::endl;
    // initialize window
    this->flags = 0;
    if (fullscreen)
    {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }
    if (vsync)
    {
        flags = flags | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    }
    this->running = true;
    //if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        /*std::cout << "Subsystems Initialised" << std::endl;
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
        }*/
    }
    // window icon
    /*SDL_Surface *iconSurface = SDL_LoadBMP("assets/img/icon/window_icon.bmp");
    if (!iconSurface)
    {
        std::cout << "Failed to load icon: " << IMG_GetError() << std::endl;
    }
    SDL_SetWindowIcon(this->window, iconSurface);
    SDL_FreeSurface(iconSurface);*/

    this->structureFactory = StructureFactory::getInstance();
    loadMedia();
    std::cout << "================= new Map() =================" << std::endl;
    this->map = new Map(&this->tickManager, &this->structureFactory, &this->perlinNoise);
    loadEntities();
    std::cout << "================= itemFactory.init() =================" << std::endl;
    this->itemFactory.init();
    loadItems();

    /*std::cout << "================= new MouseManager() =================" << std::endl;
    this->mouseManager = new MouseManager();*/
    std::cout << "================= new GUIManager() =================" << std::endl;
    std::cout << "====================================================" << std::endl;
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
        std::vector<Player *> *players = this->map->getEntityManager()->getPlayers();
        int size = players->size();
        for (int i = 0; i < size; i++)
        {
            (*players)[i]->handleEvents(&this->event);
        }
    }
}

TimeData timeData = {SDL_GetTicks64(), 0, 1000, SDL_GetTicks64(), 0};
void Game::update()
{
    // if (limiter("UPS", timeData.counterLimiter, 1000 / this->fixedUPS, timeData.lastTimeLimiter))
    this->map->update();

    // countPrinter("UPS", timeData.counter, timeData.interval, timeData.lastTime);
}

TimeData timeData2 = {SDL_GetTicks64(), 0, 1000, SDL_GetTicks64(), 0};
void Game::render()
{
    // if (limiter("FPS", timeData2.counterLimiter, 1000 / this->fixedFPS, timeData2.lastTimeLimiter))
    //SDL_RenderClear(this->renderer);

    std::vector<Player *> *players = this->map->getEntityManager()->getPlayers();
    int size = players->size();
    for (int i = 0; i < size; i++)
    {
        (*players)[i]->render();
    }

    //SDL_RenderPresent(this->renderer);
    // countPrinter("FPS", timeData2.counter, timeData2.interval, timeData2.lastTime);
}

void Game::clean()
{
    delete this->map;
    this->audioManager.free();

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
    Camera *camera = new Camera(this->screenWidth, this->screenHeight, this->flags, 10, 20000, this->title, 0, 0);
    Player *player = new Player("Player", 0, 0, 1, 1, 103, this->map, camera);
    this->map->addPlayer(player);
    Camera *camera2 = new Camera(this->screenWidth, this->screenHeight, this->flags, 10, 20000, this->title, 0, 0);
    Player *player2 = new Player("GREEN", 0, 0, 1, 1, 103, this->map, camera);
    this->map->addPlayer(player2);

    // test
    Entity *warrior = new Entity("Warrior", 0, 0, 1, 1, 101, this->map);
    warrior->setBehavior(new WarriorBehavior(warrior));
    this->map->addEntity(warrior);
    // this->map->addEntity(new Entity(this->textureManager.getTexture("Explorer"), 0, 0, 1, 1, 102, this->map, new ExplorerBehavior()));
}

void Game::loadItems()
{
    std::cout << "================= Game::LoadItems() =================" << std::endl;
    this->itemFactory.load();
}
