#ifndef camera_hpp
#define camera_hpp

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <iostream>

class Entity;

// source : https://lazyfoo.net/tutorials/SDL/30_scrolling/index.php
// Texture wrapper class
class Camera
{
public:
    Camera(SDL_Renderer *renderer, int width, int height, double minScale, double maxScale, float positionX, float positionY) : renderer(renderer), width(width), height(height), minScale(minScale), maxScale(1 / maxScale), positionX(positionX), positionY(positionY), velX(0), velY(0), scale(1.0), scaleSpeed(1.0), velocity(1), sprintVelocity(50) { std::cout << "camera zoom need fix" << std::endl; };
    ~Camera();

    void handleEvents(SDL_Event *event);
    void update();
    void move();
    void render(Entity *entity);
    void render(SDL_Rect renderBox, Texture *texture);
    void render(SDL_Rect srcBox, SDL_Rect dstBox, Texture *texture);

    SDL_Rect convertInGameToCameraCoordinates(SDL_FRect &rect);
    std::pair<float, float> convertCameraToInGameCoordinates(int x, int y);
    // return true if rect coordinates are contained in the screen
    bool isVisibleOnScreen(SDL_Rect rect);

    void setPosition(int x, int y);
    float getPositionX();
    float getPositionY();
    int getWidth();
    int getHeight();
    double getScale();
    SDL_Renderer *getRenderer();

private:
    // Image dimensions
    int width, height;
    float velX, velY;
    double scale, scaleSpeed, minScale, maxScale;

    // in-game coordinates
    float positionX, positionY;
    int velocity;
    int sprintVelocity;

    SDL_Renderer *renderer;
};

#endif
