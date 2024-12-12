#ifndef texture_hpp
#define texture_hpp

#define TEXTURE_DEFAULT_SIZE 32

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

// source : https://lazyfoo.net/tutorials/SDL/10_color_keying/index.php
// Texture wrapper class
class Texture
{
public:
    Texture();
    Texture(SDL_Renderer *renderer);
    ~Texture();

    Texture *loadFromFile(std::string path);
    Texture *loadFromRenderedText(TTF_Font *font, std::string text, const SDL_Color& textColor);
    void free();
    void render(const int& x, const int& y);
    void render(const int& x, const int& y, const int& w, const int& h);
    void render(const SDL_Rect& renderBox);
    void render(const SDL_Rect& srcBox, const SDL_Rect& dstBox);

    int getWidth();
    int getHeight();
    void setSize(const int& width, const int& height);
    int getCenterX();
    int getCenterY();
    int getId();
    int getTextureDefaultSize();

private:
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    int width, height;
    int id;
};

#endif