#ifndef gui_manager_hpp
#define gui_manager_hpp

#include "SDL2/SDL_events.h"
extern "C"
{
#include "microui.h"
#include "renderer.h"
}

class GUIManager
{
public:
    GUIManager();
    ~GUIManager();

    void init(SDL_Window *windows, SDL_Renderer *renderer);
    bool isMouseOverGUI(int x, int y);
    bool handleEvents(SDL_Event *event);
    void render();

private:
    SDL_Renderer *renderer;
    char logbuf[64000];
    int logbuf_updated = 0;
    // float bg[3] = {90, 95, 100};
    mu_Context ctx;
    char button_map[256];
    char key_map[256];
};

#endif
