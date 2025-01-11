#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <stdio.h>
#include "renderer.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static TTF_Font *font;

void r_init(SDL_Window *window1, SDL_Renderer *renderer1)
{
    window = window1;
    renderer = renderer1;
    font = TTF_OpenFont("assets/fonts/Raleway-Medium.ttf", 24);
    if (!font)
    {
        return;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void r_draw_rect(mu_Rect rect, mu_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect sdl_rect = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderFillRect(renderer, &sdl_rect);
}

void r_init_font(const char *font_path, int font_size)
{
    if (TTF_Init() == -1)
    {
        exit(1);
    }

    font = TTF_OpenFont(font_path, font_size);
    if (!font)
    {
        exit(1);
    }
}

void r_draw_text(const char *text, mu_Vec2 pos, mu_Color color)
{
    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, sdl_color);
    if (!surface)
    {
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst_rect = {pos.x, pos.y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void r_draw_icon(int id, mu_Rect rect, mu_Color color)
{
    /*mu_Rect src = atlas[id];
    int x = rect.x + (rect.w - src.w) / 2;
    int y = rect.y + (rect.h - src.h) / 2;*/
}

int r_get_text_width(const char *text, int len)
{
    int res = 0;
    /*for (const char *p = text; *p && len--; p++) {
      if ((*p & 0xc0) == 0x80) { continue; }
      int chr = mu_min((unsigned char) *p, 127);
      res += atlas[ATLAS_FONT + chr].w;
    }*/
    return res;
}

int r_get_text_height(void)
{
    return 18;
}

void r_set_clip_rect(mu_Rect rect)
{
    SDL_Rect sdl_rect = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderSetClipRect(renderer, &sdl_rect);
}

void r_clear(mu_Color clr)
{
    SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
    SDL_RenderClear(renderer);
}

void r_present(void)
{
    SDL_RenderPresent(renderer);
}
