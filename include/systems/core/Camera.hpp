#ifndef camera_hpp
#define camera_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <iostream>

class Entity;
class Texture;
class TextureManager;

// source : https://lazyfoo.net/tutorials/SDL/30_scrolling/index.php
// Texture wrapper class
class Camera
{
public:
    //Camera(SDL_Renderer *renderer, int width, int height, double minScale, double maxScale, float positionX, float positionY, TextureManager *textureManager) : renderer(renderer), width(width), height(height), minScale(minScale), maxScale(1 / maxScale), positionX(positionX), positionY(positionY), textureManager(textureManager), velX(0), velY(0), scale(1.0), scaleSpeed(1.0), velocityMultiplier(4.0 / 16), sprintVelocity(50), backgroundTexture(textureManager->getTexture("BACKGROUND")), backgroundRenderRect({(int)((this->width / 2) - (this->backgroundTexture->getCenterX())), (int)((this->height / 2) - (this->backgroundTexture->getCenterY())), (int)(this->backgroundTexture->getWidth()), (int)(this->backgroundTexture->getHeight())}) { std::cout << "camera zoom need fix" << std::endl; };
    Camera(int width, int height, double minScale, double maxScale, float positionX, float positionY, TextureManager *textureManager) : renderer(), width(width), height(height), minScale(minScale), maxScale(1 / maxScale), positionX(positionX), positionY(positionY), textureManager(textureManager), velX(0), velY(0), scale(1.0), scaleSpeed(1.0), velocityMultiplier(4.0 / 16), sprintVelocity(50), backgroundTexture(textureManager->getTexture("BACKGROUND")), backgroundRenderRect({(int)((this->width / 2) - (this->backgroundTexture->getCenterX())), (int)((this->height / 2) - (this->backgroundTexture->getCenterY())), (int)(this->backgroundTexture->getWidth()), (int)(this->backgroundTexture->getHeight())})
    {
        std::cout << "camera zoom need fix" << std::endl;

    };
    ~Camera();

    void handleEvents(SDL_Event *event);
    void update();
    void move();
    void render(const Entity *entity);
    void render(const Texture *texture, SDL_Rect renderBox);
    void render(const Texture *texture, SDL_Rect srcBox, SDL_Rect dstBox);
    void renderBackground();

    SDL_Rect convertInGameToCameraCoordinates(SDL_FRect rect);
    std::pair<float, float> convertCameraToInGameCoordinates(int x, int y);
    // return true if rect coordinates are contained in the screen
    bool isVisibleOnScreen(const SDL_Rect rect);

    void setPosition(float x, float y);
    float getPositionX();
    float getPositionY();
    int getWidth();
    int getHeight();
    double getScale();
    SDL_Renderer *getRenderer();
    TextureManager *getTextureManager();

private:
    // Image dimensions
    int width, height;
    float velX, velY;
    double scale, scaleSpeed, minScale, maxScale;

    // in-game coordinates
    float positionX, positionY;
    float velocityMultiplier;
    float sprintVelocity;

    SDL_Renderer *renderer;
    TextureManager *textureManager;
    Texture *backgroundTexture;
    SDL_Rect backgroundRenderRect;
};

#endif
