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
    Texture(SDL_Renderer *renderer);
    ~Texture();

    Texture *loadFromFile(const char *path);
    Texture *loadFromRenderedText(std::string path, SDL_Color textColor);
    // Deallocates texture
    void free();

    // render image with choosen width and height
    void render(SDL_Rect renderBox);

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
    SDL_Renderer *renderer;

    // Image dimensions
    int width, height;
    int id;
};

#endif