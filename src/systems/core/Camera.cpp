#include "systems/core/Camera.hpp"

#include <iostream>

#include "entities/Entity.hpp"
#include "Texture.hpp"
#include "systems/utils/Constants.hpp"
#include "map/Tile.hpp"

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
            upVelY = this->velocityMultiplier;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            downVelY = this->velocityMultiplier;
            break;
        case SDLK_LEFT:
        case SDLK_q:
            leftVelX = this->velocityMultiplier;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            rightVelX = this->velocityMultiplier;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            sprint = sprintVelocity;
            break;
        case SDLK_0:
            this->scale = BASE_SCALE;
            break;
        case SDLK_DELETE:
            this->positionX = 0;
            this->positionY = 0;
            break;
        }
        this->velX = sprint * (rightVelX - leftVelX);
        this->velY = sprint * (downVelY - upVelY);
    }
    // if mouse wheel moved
    if (event->type == SDL_MOUSEWHEEL)
    {
        if (event->wheel.y > 0)
        {
            double newScale = this->scale + this->scaleSpeed;
            if (newScale < this->minScale)
            {
                this->scale = newScale;
            }
        }
        else if (event->wheel.y < 0)
        {
            double newScale = this->scale - this->scaleSpeed;
            if (newScale > this->maxScale)
            {
                this->scale = newScale;
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
        this->velX = sprint * (rightVelX - leftVelX);
        this->velY = sprint * (downVelY - upVelY);
    }
}

void Camera::update()
{
    move();
}

void Camera::move()
{
    this->positionX += this->velocityMultiplier * velX;
    this->positionY += this->velocityMultiplier * velY;
}

void Camera::render(const Entity *entity)
{
    SDL_FRect renderBox = entity->getHitBox();
    SDL_Rect newRenderBox = convertInGameToCameraCoordinates(renderBox);
    if (isVisibleOnScreen(newRenderBox))
    {
        render(this->textureManager->getTexture(entity->getTextureName()), newRenderBox);
    }
}

void Camera::render(const Tile *tile)
{
    SDL_FRect renderBox = {tile->getPositionX(), tile->getPositionY(), 1, 1};
    SDL_Rect newRenderBox = convertInGameToCameraCoordinates(renderBox);
    render(this->textureManager->getTexture(tile->getTextureName()), newRenderBox);
}

void Camera::render(const Texture *texture, SDL_Rect renderBox)
{
    SDL_RenderCopy(this->renderer, texture->getTexture(), NULL, &renderBox);
}

void Camera::render(const Texture *texture, SDL_Rect srcBox, SDL_Rect dstBox)
{
    SDL_RenderCopy(this->renderer, texture->getTexture(), &srcBox, &dstBox);
}

void Camera::renderBackground() { render(this->backgroundTexture, backgroundRenderRect); }

SDL_Rect Camera::convertInGameToCameraCoordinates(SDL_FRect rect)
{
    float cameraPositionX = this->positionX * TILE_PIXELS_SIZE;
    float cameraPositionY = this->positionY * TILE_PIXELS_SIZE;
    float viewCenterX = this->width / 2;
    float viewCenterY = this->height / 2;

    int viewPositionX = (viewCenterX - cameraPositionX * scale) + (rect.x * TILE_PIXELS_SIZE * scale);
    int viewPositionY = (viewCenterY - cameraPositionY * scale) + (rect.y * TILE_PIXELS_SIZE * scale);

    SDL_Rect res = {viewPositionX, viewPositionY, rect.w * TILE_PIXELS_SIZE * scale, rect.h * TILE_PIXELS_SIZE * scale};
    return res;
}

std::pair<float, float> Camera::convertCameraToInGameCoordinates(int x, int y)
{
    float cameraPositionX = this->positionX * TILE_PIXELS_SIZE;
    float cameraPositionY = this->positionY * TILE_PIXELS_SIZE;
    float viewCenterX = this->width / 2;
    float viewCenterY = this->height / 2;

    float newX = (-viewCenterX + cameraPositionX * scale + x) / this->scale;
    float newY = (-viewCenterY + cameraPositionY * scale + y) / this->scale;
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
    if (viewBottomRightPositionX < 0 || viewBottomRightPositionY < 0 || rect.x > this->width || rect.y > this->height)
    {
        return false;
    }
    return true;
}

void Camera::setPosition(float x, float y)
{
    this->positionX = x;
    this->positionY = y;
}

float Camera::getPositionX() { return this->positionX; }
float Camera::getPositionY() { return this->positionY; }
int Camera::getWidth() { return this->width; }
int Camera::getHeight() { return this->height; }
double Camera::getScale() { return this->scale; }
SDL_Window *Camera::getWindow() { return this->window; }
SDL_Renderer *Camera::getRenderer() { return this->renderer; }
TextureManager *Camera::getTextureManager() { return this->textureManager; }
