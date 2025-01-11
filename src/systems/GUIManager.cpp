#include "systems/GUIManager.hpp"

#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

GUIManager::GUIManager() {}
GUIManager::~GUIManager() {}
void GUIManager::init(SDL_Window *window, SDL_Renderer *renderer)
{
    this->button_map[SDL_BUTTON_LEFT & 0xff] = MU_MOUSE_LEFT;
    this->button_map[SDL_BUTTON_RIGHT & 0xff] = MU_MOUSE_RIGHT;
    this->button_map[SDL_BUTTON_MIDDLE & 0xff] = MU_MOUSE_MIDDLE;
    this->key_map[SDLK_LSHIFT & 0xff] = MU_KEY_SHIFT;
    this->key_map[SDLK_RSHIFT & 0xff] = MU_KEY_SHIFT;
    this->key_map[SDLK_LCTRL & 0xff] = MU_KEY_CTRL;
    this->key_map[SDLK_RCTRL & 0xff] = MU_KEY_CTRL;
    this->key_map[SDLK_LALT & 0xff] = MU_KEY_ALT;
    this->key_map[SDLK_RALT & 0xff] = MU_KEY_ALT;
    this->key_map[SDLK_RETURN & 0xff] = MU_KEY_RETURN;
    this->key_map[SDLK_BACKSPACE & 0xff] = MU_KEY_BACKSPACE;

    r_init(window, renderer);
    mu_init(&this->ctx);
    ctx.text_width = text_width;
    ctx.text_height = text_height;
    this->renderer = renderer;
}

bool GUIManager::isMouseOverGUI(int x, int y)
{
    mu_Container *hoveredContainer = this->ctx.hover_root;
    if (hoveredContainer)
    {
        mu_Rect rect = hoveredContainer->rect;
        return (x >= rect.x && x <= rect.x + rect.w &&
                y >= rect.y && y <= rect.y + rect.h);
    }
    return false;
}

bool GUIManager::handleEvents(SDL_Event *event)
{
    bool eventConsumed = false;
    switch (event->type)
    {
    case SDL_QUIT:
        exit(EXIT_SUCCESS);
        break;
    case SDL_MOUSEMOTION:
        mu_input_mousemove(&this->ctx, event->motion.x, event->motion.y);
        eventConsumed = true;
        break;
    case SDL_MOUSEWHEEL:
        mu_input_scroll(&this->ctx, 0, event->wheel.y * -30);
        eventConsumed = true;
        break;
    case SDL_TEXTINPUT:
        mu_input_text(&this->ctx, event->text.text);
        eventConsumed = true;
        break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    {
        if (isMouseOverGUI(event->button.x, event->button.y))
        {
            int b = this->button_map[event->button.button & 0xff];
            if (b && event->type == SDL_MOUSEBUTTONDOWN)
            {
                mu_input_mousedown(&this->ctx, event->button.x, event->button.y, b);
                eventConsumed = true;
            }
            if (b && event->type == SDL_MOUSEBUTTONUP)
            {
                mu_input_mouseup(&this->ctx, event->button.x, event->button.y, b);
                eventConsumed = true;
            }
        }
        break;
    }

    case SDL_KEYDOWN:
    case SDL_KEYUP:
    {
        int c = this->key_map[event->key.keysym.sym & 0xff];
        if (c && event->type == SDL_KEYDOWN)
        {
            mu_input_keydown(&this->ctx, c);
            eventConsumed = true;
        }
        if (c && event->type == SDL_KEYUP)
        {
            mu_input_keyup(&this->ctx, c);
            eventConsumed = true;
        }
        break;
    }
    }

    return eventConsumed;
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

void GUIManager::process_frame(mu_Context *ctx)
{
    mu_begin(ctx);
    test_window(ctx);
    mu_end(ctx);
}

void GUIManager::render()
{
    process_frame(&this->ctx);
    mu_Command *cmd = NULL;
    while (mu_next_command(&this->ctx, &cmd))
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
}
