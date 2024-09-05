#ifndef ltexture_hpp
#define ltexture_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// source : https://lazyfoo.net/tutorials/SDL/10_color_keying/index.php
// Texture wrapper class
class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile(const char *path, SDL_Renderer *renderer);
    // Deallocates texture
    void free();
    void render(SDL_Renderer *renderer, int x, int y);

    // Gets image dimensions
    int getWidth();
    int getHeight();
    void setSize(int width, int height);

private:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int width;
    int height;
};

#endif