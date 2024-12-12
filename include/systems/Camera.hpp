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
    Camera();
    ~Camera();

    void init(const int &width, const int &height, const double& minScale, const double &maxScale, const int& positionX, const int &positionY);
    void handleEvents(SDL_Event *event);
    void update();
    void move();

    void convertInGameToCameraCoordinates(const SDL_Rect &rect);
    void convertCameraToInGameCoordinates(const int &x, const int &y);
    bool isVisible(const SDL_Rect &rect);

    void setPosition(const int &x, const int& y);
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
