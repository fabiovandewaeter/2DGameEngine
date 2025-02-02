#ifndef camera_hpp
#define camera_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// source : https://lazyfoo.net/tutorials/SDL/30_scrolling/index.php
// Texture wrapper class
class Camera
{
public:
    Camera(int width, int height, double minScale, double maxScale, int positionX, int positionY) : width(width), height(height), minScale(minScale), maxScale(1 / maxScale), positionX(positionX), positionY(positionY), velX(0), velY(0), scale(1.0), scaleSpeed(1.0), velocity(1), sprintVelocity(50) {};
    ~Camera();

    void handleEvents(SDL_Event *event);
    void update();
    void move();

    void convertInGameToCameraCoordinates(SDL_Rect &rect);
    void convertCameraToInGameCoordinates(int &x, int &y);
    bool isVisible(SDL_Rect rect);

    void setPosition(int x, int y);
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
