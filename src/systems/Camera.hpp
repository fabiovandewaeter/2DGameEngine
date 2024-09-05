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

    void init(int maxWidth, int maxHeight, int width, int height, int positionX, int positionY);
    void handleEvents(SDL_Event *event);
    bool update();
    bool move();
    
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();

private:
    // Image dimensions
    int width, height;
    int maxWidth, maxHeight;
    int velX, velY;
    int positionX, positionY;
    int VELOCITY;
    int SPRINT_VELOCITY;
};

#endif