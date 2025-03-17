#include "systems/core/Camera.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "Texture.hpp"
#include "systems/utils/Constants.hpp"
#include "map/Tile.hpp"
#include "structures/Structure.hpp"

Camera::~Camera()
{
    std::cout << "\n\n\n\n\n\n\nDESTROY" << std::endl;
    delete textureManager;
    delete backgroundTexture;
    std::cout << "\n\n\n\n\n\n\nDESTROY" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

const double BASE_SCALE = 1.0;
// 1 if false and sprintVelocity if true
float sprint = 1;
float leftVelX = 0, rightVelX = 0, upVelY = 0, downVelY = 0;

void Camera::handleEvents(SDL_Event *event)
{
    // If a key was pressed
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
    {
        // Adjust the velocity
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_z:
            upVelY = velocityMultiplier;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            downVelY = velocityMultiplier;
            break;
        case SDLK_LEFT:
        case SDLK_q:
            leftVelX = velocityMultiplier;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            rightVelX = velocityMultiplier;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            sprint = sprintVelocity;
            break;
        case SDLK_0:
            scale = BASE_SCALE;
            break;
        case SDLK_DELETE:
            positionX = 0;
            positionY = 0;
            break;
        }
        velocityX = sprint * (rightVelX - leftVelX);
        velocityY = sprint * (downVelY - upVelY);
    }
    // if mouse wheel moved
    if (event->type == SDL_MOUSEWHEEL)
    {
        if (event->wheel.y > 0)
        {
            double newScale = scale + scaleSpeed;
            if (newScale < minScale)
            {
                scale = newScale;
            }
        }
        else if (event->wheel.y < 0)
        {
            double newScale = scale - scaleSpeed;
            if (newScale > maxScale)
            {
                scale = newScale;
            }
        }
    }
    // If a key was released
    else if (event->type == SDL_KEYUP && event->key.repeat == 0)
    {
        // Adjust the velocity
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_z:
            upVelY = 0;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            downVelY = 0;
            break;
        case SDLK_LEFT:
        case SDLK_q:
            leftVelX = 0;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            rightVelX = 0;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            sprint = 1;
            break;
        }
        velocityX = sprint * (rightVelX - leftVelX);
        velocityY = sprint * (downVelY - upVelY);
    }
}

void Camera::update()
{
    if (active)
    {
        SDL_ShowWindow(window);
    }
    else
    {
        SDL_HideWindow(window);
    }
    move();
}

void Camera::move()
{
    positionX += velocityMultiplier * velocityX;
    positionY += velocityMultiplier * velocityY;
}

void Camera::render(const Entity *entity)
{
    SDL_FRect renderBox = entity->getHitBox();
    SDL_Rect newRenderBox = convertInGameToCameraCoordinates(renderBox);
    if (isVisibleOnScreen(newRenderBox))
    {
        render(textureManager->getTexture(entity->getTextureName()), newRenderBox);
    }
}

void Camera::render(const Tile *tile)
{
    SDL_FRect renderBox = {tile->getPositionX(), tile->getPositionY(), 1, 1};
    SDL_Rect newRenderBox = convertInGameToCameraCoordinates(renderBox);
    render(textureManager->getTexture(tile->getTextureName()), newRenderBox);
}

void Camera::render(const Structure *structure)
{
    SDL_FRect renderBox = structure->getHitBox();
    SDL_Rect newRenderBox = convertInGameToCameraCoordinates(renderBox);
    if (isVisibleOnScreen(newRenderBox))
    {
        render(textureManager->getTexture(structure->getTextureName()), newRenderBox);
    }
}

void Camera::render(const Texture *texture, SDL_Rect renderBox)
{
    SDL_RenderCopy(renderer, texture->getTexture(), NULL, &renderBox);
}

void Camera::render(const Texture *texture, SDL_Rect srcBox, SDL_Rect dstBox)
{
    SDL_RenderCopy(renderer, texture->getTexture(), &srcBox, &dstBox);
}

void Camera::renderBackground() { render(backgroundTexture, backgroundRenderRect); }

SDL_Rect Camera::convertInGameToCameraCoordinates(SDL_FRect rect)
{
    float cameraPositionX = positionX * TILE_PIXELS_SIZE;
    float cameraPositionY = positionY * TILE_PIXELS_SIZE;
    float viewCenterX = windowWidth / 2;
    float viewCenterY = windowHeight / 2;

    int viewPositionX = (viewCenterX - cameraPositionX * scale) + (rect.x * TILE_PIXELS_SIZE * scale);
    int viewPositionY = (viewCenterY - cameraPositionY * scale) + (rect.y * TILE_PIXELS_SIZE * scale);

    SDL_Rect res = {viewPositionX, viewPositionY, rect.w * TILE_PIXELS_SIZE * scale, rect.h * TILE_PIXELS_SIZE * scale};
    return res;
}

std::pair<float, float> Camera::convertCameraToInGameCoordinates(int x, int y)
{
    float cameraPositionX = positionX * TILE_PIXELS_SIZE;
    float cameraPositionY = positionY * TILE_PIXELS_SIZE;
    float viewCenterX = windowWidth / 2;
    float viewCenterY = windowHeight / 2;

    float newX = (-viewCenterX + cameraPositionX * scale + x) / scale;
    float newY = (-viewCenterY + cameraPositionY * scale + y) / scale;
    newX = newX / TILE_PIXELS_SIZE;
    newY = newY / TILE_PIXELS_SIZE;
    std::pair<float, float> res = {newX, newY};
    std::cout << newX << " " << newY << std::endl;
    return res;
}

bool Camera::isVisibleOnScreen(SDL_Rect rect)
{
    int viewBottomRightPositionX = rect.x + rect.w;
    int viewBottomRightPositionY = rect.y + rect.h;
    if (viewBottomRightPositionX < 0 || viewBottomRightPositionY < 0 || rect.x > windowWidth || rect.y > windowHeight)
    {
        return false;
    }
    return true;
}

float Camera::getPositionX() const { return positionX; }
float Camera::getPositionY() const { return positionY; }
int Camera::getWindowWidth() const { return windowWidth; }
int Camera::getWindowHeight() const { return windowHeight; }
double Camera::getScale() const { return scale; }
SDL_Window *Camera::getWindow() const { return window; }
Uint32 Camera::getWindowID() const { return windowID; }
SDL_Renderer *Camera::getRenderer() const { return renderer; }
TextureManager *Camera::getTextureManager() const { return textureManager; }
bool Camera::isActive() const { return active; }

void Camera::setPosition(float x, float y)
{
    positionX = x;
    positionY = y;
}
