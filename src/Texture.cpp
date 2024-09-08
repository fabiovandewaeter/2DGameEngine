#include "Texture.hpp"

int idCounter = 0;

Texture::Texture()
{
    // Initialize
    texture = NULL;
    width = 0;
    height = 0;
    this->id = idCounter;
    idCounter++;
}
Texture::~Texture()
{
    // Deallocate
    free();
}
void Texture::free()
{
    // Free texture if it exists
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

bool Texture::loadFromFile(const char *path, SDL_Renderer *renderer)
{
    // Get rid of preexisting texture
    free();
    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        else
        {
            // Get image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    texture = newTexture;
    return texture != NULL;
}

void Texture::render(SDL_Renderer *renderer, SDL_Rect renderBox)
{
    // Set rendering space and render to screen
    SDL_RenderCopy(renderer, texture, NULL, &renderBox);
}

int Texture::getWidth()
{
    return width;
}
int Texture::getHeight()
{
    return height;
}
void Texture::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}
int Texture::getCenterX(){
    return this->getWidth()/2;
}
int Texture::getCenterY(){
    return this->getHeight()/2;
}
int Texture::getId(){
    return this->id;
}