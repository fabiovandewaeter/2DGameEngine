#ifndef texture_hpp
#define texture_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// source : https://lazyfoo.net/tutorials/SDL/10_color_keying/index.php
// Texture wrapper class
class Texture
{
public:
    Texture();
    ~Texture();

    bool loadFromFile(const char *path, SDL_Renderer *renderer);
    // Deallocates texture
    void free();

    // render image with choosen width and height
    void render(SDL_Renderer *renderer, SDL_Rect renderBox);

    // Gets image dimensions
    int getWidth();
    int getHeight();
    void setSize(int width, int height);
    int getCenterX();
    int getCenterY();
    int getId();

private:
    // The actual hardware texture
    SDL_Texture *texture;

    // Image dimensions
    int width;
    int height;
    
    int id;
};

#endif