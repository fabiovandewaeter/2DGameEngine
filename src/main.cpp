#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "microui.hpp"

#include "Game.hpp"

#include "systems/TickManager.hpp"


void render_gui(mu_Context *ctx) {
    if (mu_begin_window(ctx, "Inventaire", mu_rect(10, 10, 300, 200))) {
        mu_label(ctx, "Slot 1: Objet A");
        if (mu_button(ctx, "Utiliser")) {
            printf("Objet utilisé\n");
        }
        mu_end_window(ctx);
    }
}

mu_Context ctx;
Game game;

int main(int argc, char *argv[])
{

    unsigned int width = 800;
    unsigned int height = 600;
    unsigned int UPS = 60;
    int vsync = 1;
    if (argc == 2)
    {
        UPS = std::atoi(argv[1]);
    }
    if (argc >= 3)
    {
        width = std::atoi(argv[1]);
        height = std::atoi(argv[2]);
    }
    if (argc >= 4)
    {
        UPS = std::atoi(argv[3]);
    }
    if (argc >= 5)
    {
        vsync = std::atoi(argv[4]);
    }
    std::cout << "Window width: " << width << std::endl;
    std::cout << "Window height: " << height << std::endl;
    std::cout << "UPS: " << UPS << std::endl;
    std::cout << "vsync: " << (vsync ? "true" : "false") << std::endl;

    mu_init(&ctx);
    game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false, vsync);
    game.setUPS(UPS);

    TickManager *tickManager = TickManager::getInstance();

    while (game.running())
    {
        tickManager->setFrameStart();
        game.handleEvents();
        game.update();
        render_gui(&ctx);
        game.render();

        tickManager->handleTickSpeed(game.getFrameDelay());
#ifdef PROFILER
        FrameMark;
#endif
    }

    game.clean();
    return 0;
}
