#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif
extern "C"
{
#include "microui.h"
#include "renderer.h"
}
#include <array>

#include "Game.hpp"
#include "systems/TickManager.hpp"

static SDL_Renderer *sdlRenderer;
static char logbuf[64000];
static int logbuf_updated = 0;
static float bg[3] = {90, 95, 100};
mu_Context ctx;
static char button_map[256];
static char key_map[256];

Game game;

static int text_width(mu_Font font, const char *text, int len)
{
  if (len == -1)
  {
    len = strlen(text);
  }
  return r_get_text_width(text, len);
}

static int text_height(mu_Font font)
{
  return r_get_text_height();
}

static void test_window(mu_Context *ctx)
{
  /* do window */
  if (mu_begin_window(ctx, "Demo Window", mu_rect(40, 40, 300, 450)))
  {
    mu_Container *win = mu_get_current_container(ctx);
    win->rect.w = mu_max(win->rect.w, 240);
    win->rect.h = mu_max(win->rect.h, 300);

    /* window info */
    if (mu_header(ctx, "Window Info"))
    {
      mu_Container *win = mu_get_current_container(ctx);
      char buf[64];
      mu_layout_row(ctx, 2, (int[]){54, -1}, 0);
      mu_label(ctx, "Position:");
      sprintf(buf, "%d, %d", win->rect.x, win->rect.y);
      mu_label(ctx, buf);
      mu_label(ctx, "Size:");
      sprintf(buf, "%d, %d", win->rect.w, win->rect.h);
      mu_label(ctx, buf);
    }

    /* labels + buttons */
    if (mu_header_ex(ctx, "Test Buttons", MU_OPT_EXPANDED))
    {
      mu_layout_row(ctx, 3, (int[]){86, -110, -1}, 0);
      mu_label(ctx, "Test buttons 1:");
      if (mu_button(ctx, "Button 1"))
      {
      }
      if (mu_button(ctx, "Button 2"))
      {
      }
      mu_label(ctx, "Test buttons 2:");
      if (mu_button(ctx, "Button 3"))
      {
      }
      if (mu_button(ctx, "Popup"))
      {
        mu_open_popup(ctx, "Test Popup");
      }
      if (mu_begin_popup(ctx, "Test Popup"))
      {
        mu_button(ctx, "Hello");
        mu_button(ctx, "World");
        mu_end_popup(ctx);
      }
    }

    mu_end_window(ctx);
  }
}

void init_ui(SDL_Renderer *renderer)
{
  mu_init(&ctx);
  ctx.text_width = text_width;
  ctx.text_height = text_height;
  sdlRenderer = renderer;
}

static int uint8_slider(mu_Context *ctx, unsigned char *value, int low, int high)
{
  static float tmp;
  mu_push_id(ctx, &value, sizeof(value));
  tmp = *value;
  int res = mu_slider_ex(ctx, &tmp, low, high, 0, "%.0f", MU_OPT_ALIGNCENTER);
  *value = tmp;
  mu_pop_id(ctx);
  return res;
}

static void process_frame(mu_Context *ctx)
{
  mu_begin(ctx);
  test_window(ctx);
  mu_end(ctx);
}

int main(int argc, char *argv[])
{
  button_map[SDL_BUTTON_LEFT & 0xff] = MU_MOUSE_LEFT;
  button_map[SDL_BUTTON_RIGHT & 0xff] = MU_MOUSE_RIGHT;
  button_map[SDL_BUTTON_MIDDLE & 0xff] = MU_MOUSE_MIDDLE;
  key_map[SDLK_LSHIFT & 0xff] = MU_KEY_SHIFT;
  key_map[SDLK_RSHIFT & 0xff] = MU_KEY_SHIFT;
  key_map[SDLK_LCTRL & 0xff] = MU_KEY_CTRL;
  key_map[SDLK_RCTRL & 0xff] = MU_KEY_CTRL;
  key_map[SDLK_LALT & 0xff] = MU_KEY_ALT;
  key_map[SDLK_RALT & 0xff] = MU_KEY_ALT;
  key_map[SDLK_RETURN & 0xff] = MU_KEY_RETURN;
  key_map[SDLK_BACKSPACE & 0xff] = MU_KEY_BACKSPACE;

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

  game.init("TestEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false, vsync);
  game.setUPS(UPS);
  r_init(game.getWindow(), game.getRenderer());
  init_ui(game.getRenderer());

  TickManager *tickManager = TickManager::getInstance();

  while (game.running())
  {
    tickManager->setFrameStart();
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_QUIT:
        exit(EXIT_SUCCESS);
        break;
      case SDL_MOUSEMOTION:
        mu_input_mousemove(&ctx, e.motion.x, e.motion.y);
        break;
      case SDL_MOUSEWHEEL:
        mu_input_scroll(&ctx, 0, e.wheel.y * -30);
        break;
      case SDL_TEXTINPUT:
        mu_input_text(&ctx, e.text.text);
        break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      {
        int b = button_map[e.button.button & 0xff];
        if (b && e.type == SDL_MOUSEBUTTONDOWN)
        {
          mu_input_mousedown(&ctx, e.button.x, e.button.y, b);
        }
        if (b && e.type == SDL_MOUSEBUTTONUP)
        {
          mu_input_mouseup(&ctx, e.button.x, e.button.y, b);
        }
        break;
      }

      case SDL_KEYDOWN:
      case SDL_KEYUP:
      {
        int c = key_map[e.key.keysym.sym & 0xff];
        if (c && e.type == SDL_KEYDOWN)
        {
          mu_input_keydown(&ctx, c);
        }
        if (c && e.type == SDL_KEYUP)
        {
          mu_input_keyup(&ctx, c);
        }
        break;
      }
      }
    }

    game.handleEvents();
    game.update();
    game.render();

    process_frame(&ctx);

    /* render */
    mu_Command *cmd = NULL;
    while (mu_next_command(&ctx, &cmd))
    {
      switch (cmd->type)
      {
      case MU_COMMAND_TEXT:
        r_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color);
        break;
      case MU_COMMAND_RECT:
        r_draw_rect(cmd->rect.rect, cmd->rect.color);
        break;
      case MU_COMMAND_ICON:
        r_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color);
        break;
      case MU_COMMAND_CLIP:
        r_set_clip_rect(cmd->clip.rect);
        break;
      }
    }
    r_present();

    tickManager->handleTickSpeed(game.getFrameDelay());
#ifdef PROFILER
    FrameMark;
#endif
  }

  game.clean();
  return 0;
}
