#ifndef camera_hpp
#define camera_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// source : https://lazyfoo.net/tutorials/SDL/30_scrolling/index.php
// Texture wrapper class
class Camera
{
public:
    Camera();
    ~Camera();

    void handleEvents(SDL_Event *event);
    void render(int x, int y, SDL_Renderer *renderer);

    // Gets image dimensions
    int getWidth();
    int getHeight();
    void setSize(int width, int height);

private:
    // Image dimensions
    int width, height;
    int velX, velY;
};

#endif