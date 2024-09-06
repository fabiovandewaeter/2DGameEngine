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

    void init(int width, int height, double minScale, double maxScale, int positionX, int positionY);
    void handleEvents(SDL_Event *event);
    bool update();
    bool move();
    
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    double getScale();

private:
    // Image dimensions
    int width, height;
    int velX, velY;
    double scale, scaleSpeed, minScale, maxScale;
    
    // in-game coordinates
    int positionX, positionY;
    int velocity;
    int sprintVelocity;
};

#endif