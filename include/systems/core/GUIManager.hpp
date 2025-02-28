#ifndef gui_manager_hpp
#define gui_manager_hpp

#include <vector>
#include <unordered_map>
#include <string>

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_render.h"
extern "C"
{
#include "microui/microui.h"
}

class TextureManager;
class TickManager;
class StructureFactory;
class Texture;
class MouseManager;
class Player;

class GUIManager
{
public:
    GUIManager(SDL_Window *windows, SDL_Renderer *renderer, TextureManager *textureManager, TickManager *tickManager, StructureFactory *structureFactory, MouseManager *mouseManager);
    ~GUIManager();

    bool isMouseOverGUI(int x, int y);
    bool handleEvents(SDL_Event *event);
    void render(Player *player);

private:
    SDL_Renderer *renderer;
    TextureManager *textureManager;
    TickManager *tickManager;
    StructureFactory *structureFactory;
    std::vector<std::string> structureNamesList;
    std::unordered_map<std::string, int> structureTextureNameToId;
    std::vector<Texture *> structureTextureIdToTexture;
    MouseManager *mouseManager;
    mu_Context ctx;
    char button_map[256];
    char key_map[256];

    void loadConfiguration();
    void loadIcons();

    void changeMouseManagerClickOnEmptyTileStrategy(std::string structureName, Player *placedBy);

    void test_window(mu_Context *ctx, Player *player);
    void process_frame(mu_Context *ctx, Player *player);

    void r_init(SDL_Window *window1, SDL_Renderer *renderer1);
    void r_draw_rect(mu_Rect rect, mu_Color color);
    void r_init_font(const char *font_path, int font_size);
    void r_draw_text(const char *text, mu_Vec2 pos, mu_Color color);
    void r_draw_icon(int id, mu_Rect rect, mu_Color color);
    void r_set_clip_rect(mu_Rect rect);
    void r_clear(mu_Color color);
    void r_present(void);
    int uint8_slider(mu_Context *ctx, unsigned char *value, int low, int high);
};

#endif
