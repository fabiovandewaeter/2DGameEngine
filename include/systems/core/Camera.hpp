#ifndef camera_hpp
#define camera_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <iostream>

#include "systems/core/TextureManager.hpp"
#include "Texture.hpp"

class Entity;
class Tile;
class Structure;

// source : https://lazyfoo.net/tutorials/SDL/30_scrolling/index.php
// Texture wrapper class
class Camera
{
public:
    Camera(int windowWidth, int windowHeight, int flags, double minScale, double maxScale, std::string title, float positionX, float positionY, bool active) : windowWidth(windowWidth), windowHeight(windowHeight), velocityX(0), velocityY(0), scale(1.0), scaleSpeed(1.0), minScale(minScale), maxScale(1 / maxScale), positionX(positionX), positionY(positionY), velocityMultiplier(4.0 / 16), sprintVelocity(50), active(active)
    {
        if (!active)
        {
            flags |= SDL_WINDOW_HIDDEN;
        }
        std::cout << "camera zoom need fix" << std::endl;
        // Create window
        if (!(window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags)))
        {
            std::cerr << "FAIL : Window NOT created" << std::endl;
            return;
        }
        windowID = SDL_GetWindowID(window);
        // Create renderer
        if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        else
        {
            std::cerr << "FAIL : Renderer NOT created" << std::endl;
            return;
        }
        // Initialize PNG loading
        textureManager = new TextureManager(this);
        backgroundTexture = textureManager->getTexture("BACKGROUND");
        backgroundRenderRect = {(int)((windowWidth / 2) - (backgroundTexture->getCenterX())), (int)((windowHeight / 2) - (backgroundTexture->getCenterY())), (int)(backgroundTexture->getWidth()), (int)(backgroundTexture->getHeight())};
        // window icon
        SDL_Surface *iconSurface = SDL_LoadBMP("assets/img/icon/window_icon.bmp");
        if (!iconSurface)
        {
            std::cout << "Failed to load icon: " << IMG_GetError() << std::endl;
            return;
        }
        SDL_SetWindowIcon(window, iconSurface);
        SDL_FreeSurface(iconSurface);
    }

    ~Camera();

    void handleEvents(SDL_Event *event);
    void update();
    void move();
    void render(const Entity *entity);
    void render(const Tile *Tile);
    void render(const Structure *Structure);
    void render(const Texture *texture, SDL_Rect renderBox);
    void render(const Texture *texture, SDL_Rect srcBox, SDL_Rect dstBox);
    void renderBackground();

    SDL_Rect convertInGameToCameraCoordinates(SDL_FRect rect);
    std::pair<float, float> convertCameraToInGameCoordinates(int x, int y);
    // return true if rect coordinates are contained in the screen
    bool isVisibleOnScreen(const SDL_Rect rect);

    void setPosition(float x, float y);
    float getPositionX() const;
    float getPositionY() const;
    int getWindowWidth() const;
    int getWindowHeight() const;
    double getScale() const;
    SDL_Window *getWindow() const;
    Uint32 getWindowID() const;
    SDL_Renderer *getRenderer() const;
    TextureManager *getTextureManager() const;
    bool isActive() const;

private:
    // Image dimensions
    int windowWidth, windowHeight;
    float velocityX, velocityY;
    double scale, scaleSpeed, minScale, maxScale;

    // in-game coordinates
    float positionX, positionY;
    float velocityMultiplier;
    float sprintVelocity;

    // true if the Camera can render things
    bool active;

    SDL_Window *window;
    Uint32 windowID;
    SDL_Renderer *renderer;
    TextureManager *textureManager;
    Texture *backgroundTexture;
    SDL_Rect backgroundRenderRect;
};

#endif
