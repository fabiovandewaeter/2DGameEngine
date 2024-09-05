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

    void init(int maxWidth, int maxHeight, int width, int height);
    void handleEvents(SDL_Event *event);

private:
    // Image dimensions
    int width, height;
    int maxWidth, maxHeight;
    int velX, velY;
};

#endif