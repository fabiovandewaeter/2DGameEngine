#ifndef camera_hpp
#define camera_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
    Camera(int width, int height, int flags, double minScale, double maxScale, std::string title, float positionX, float positionY, TextureManager *textureManager) : width(width), height(height), minScale(minScale), maxScale(1 / maxScale), positionX(positionX), positionY(positionY), textureManager(textureManager), velX(0), velY(0), scale(1.0), scaleSpeed(1.0), velocityMultiplier(4.0 / 16), sprintVelocity(50), backgroundTexture(textureManager->getTexture("BACKGROUND")), backgroundRenderRect({(int)((this->width / 2) - (this->backgroundTexture->getCenterX())), (int)((this->height / 2) - (this->backgroundTexture->getCenterY())), (int)(this->backgroundTexture->getWidth()), (int)(this->backgroundTexture->getHeight())})
    {
        std::cout << "camera zoom need fix" << std::endl;
        if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
        {
            std::cout << "Subsystems Initialised" << std::endl;
            // Create window
            if (!(this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags)))
            {
                std::cout << "FAIL : Window NOT created" << std::endl;
            }
            // Create renderer
            if ((this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED)))
            {
                SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
                std::cout << "Renderer created" << std::endl;
            }
            else
            {
                std::cout << "FAIL : Renderer NOT created" << std::endl;
            }
            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "FAIL : SDL_image NOT initialized" << std::endl;
            }
            // Initialize SDL_ttf
            if (TTF_Init() == -1)
            {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            }
    }

    // window icon
    SDL_Surface *iconSurface = SDL_LoadBMP("assets/img/icon/window_icon.bmp");
    if (!iconSurface)
    {
        std::cout << "Failed to load icon: " << IMG_GetError() << std::endl;
    }

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

    SDL_Window *window;
    SDL_Renderer *renderer;
    TextureManager *textureManager;
    Texture *backgroundTexture;
    SDL_Rect backgroundRenderRect;
};

#endif
