#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "Game.hpp"

#include "map/Map.hpp"
#include "entities/Player.hpp"

Game::Game(std::string title, int windowPositionX, int windowPositioNY, int windowWidth, int windowHeight, bool fullscreen, bool vsync, int UPS) : title(title), FPS(60), UPS(60), windowWidth(windowWidth), windowHeight(windowHeight)
{
    std::cout << "\n======================================================" << std::endl;
    setUPS(UPS);
    std::cout << "Window width: " << windowWidth << std::endl;
    std::cout << "Window height: " << windowHeight << std::endl;
    std::cout << "UPS: " << UPS << std::endl;
    std::cout << "vsync: " << (vsync ? "true" : "false") << std::endl;
    // initialize window
    flags = 0;
    if (fullscreen)
    {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }
    if (vsync)
    {
        flags = flags | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    }
    running = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised" << std::endl;
    }
    else
    {
        std::cerr << "SDL_Init could not initialize! SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cerr << "FAIL : SDL_image NOT initialized" << std::endl;
        return;
    }
    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    structureFactory = StructureFactory::getInstance();
    loadMedia();
    std::cout << "================= new Map() =================" << std::endl;
    map = new Map(&tickManager, &structureFactory, &perlinNoise);
    loadEntities();
    std::cout << "================= itemFactory.init() =================" << std::endl;
    itemFactory.init();
    loadItems();
    std::cout << "====================================================" << std::endl;
}

Game::~Game()
{
    delete map;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::run()
{
    while (isRunning())
    {
        tickManager.setFrameStart();
        handleEvents();
        update();
        render();
        tickManager.waitTick(getFrameDelay());
        // running = false;
    }
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        else
        {
            Uint32 eventWindowID = 0;
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                eventWindowID = event.button.windowID;
                break;
            case SDL_MOUSEMOTION:
                eventWindowID = event.motion.windowID;
                break;
            case SDL_WINDOWEVENT:
                eventWindowID = event.window.windowID;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                eventWindowID = event.key.windowID;
                break;
            case SDL_MOUSEWHEEL:
                eventWindowID = event.wheel.windowID;
                break;
            }
            std::vector<Player *> *players = map->getEntityManager()->getPlayers();
            int size = players->size();
            for (int i = 0; i < size; i++)
            {
                Player *player = (*players)[i];
                if (player->getCamera()->getWindowID() == eventWindowID)
                {
                    player->handleEvents(&event);
                    break;
                }
            }
        }
    }
}

TimeData timeData = {SDL_GetTicks64(), 0, 1000, SDL_GetTicks64(), 0};
void Game::update()
{
    // if (limiter("UPS", timeData.counterLimiter, 1000 / UPS, timeData.lastTimeLimiter))
    map->update();
    if (map->getEntityManager()->getNumberOfPlayers() <= 0)
    {
        running = false;
    }
    countPrinter("UPS", timeData.counter, timeData.interval, timeData.lastTime);
}

TimeData timeData2 = {SDL_GetTicks64(), 0, 1000, SDL_GetTicks64(), 0};
void Game::render()
{
    // if (limiter("FPS", timeData2.counterLimiter, 1000 / FPS, timeData2.lastTimeLimiter))
    std::vector<Player *> *players = map->getEntityManager()->getPlayers();
    int size = players->size();
    for (int i = 0; i < size; i++)
    {
        (*players)[i]->render();
    }
    //  countPrinter("FPS", timeData2.counter, timeData2.interval, timeData2.lastTime);
}

bool Game::isRunning() { return running; }
void Game::setFPS(unsigned int fps) { FPS = fps; }

void Game::setUPS(unsigned int ups)
{
    UPS = ups;
    frameDelay = 10000000 / UPS;
}

Uint64 Game::getFrameDelay() { return frameDelay; }

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
    audioManager.init();
    audioManager.loadMedia();
    musics = audioManager.getMusics();
}

#include "entities/behaviors/WarriorBehavior.hpp"
#include "entities/behaviors/ExplorerBehavior.hpp"
void Game::loadEntities()
{
    std::cout << "================= Game::LoadEntities() =================" << std::endl;
    Camera *camera2 = new Camera(windowWidth, windowHeight, flags, 10, 20000, title, 0, 0, true);
    Player *player2 = new Player("GREEN", 0, 0, 1, 1, 100000, map, camera2);
    map->addPlayer(player2);

    Camera *camera = new Camera(windowWidth, windowHeight, flags, 10, 20000, title, 0, 0, false);
    Player *player = new Player("Player", 0, 0, 1, 1, 100000, map, camera);
    map->addPlayer(player);

    // test
    /*Entity *warrior = new Entity("Warrior", 20, 15, 1, 1, 100, map);
    warrior->setBehavior(new WarriorBehavior(warrior));
     map->addEntity(warrior);*/

    /*Entity *explorer = new Entity("Explorer", 10, 10, 1, 1, 100, map);
    explorer->setBehavior(new ExplorerBehavior(explorer));
    map->addEntity(explorer);*/
}

void Game::loadItems()
{
    std::cout << "================= Game::LoadItems() =================" << std::endl;
    itemFactory.load();
}
