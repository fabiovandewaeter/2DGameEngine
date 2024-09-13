#include "Texture.hpp"

int counter = 0;
Texture::Texture() {}
Texture::Texture(SDL_Renderer *renderer)
{
    // Initialize
    texture = NULL;
    width = 0;
    height = 0;
    this->renderer = renderer;
    this->id = counter;
    counter++;
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

Texture *Texture::loadFromFile(const char *path)
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
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        else
        {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    texture = newTexture;
    return this;
}
Texture *Texture::loadFromRenderedText(std::string text, SDL_Color textColor){
    
    return this;
}

void Texture::render(SDL_Rect renderBox)
{
    // Set rendering space and render to screen
    SDL_RenderCopy(this->renderer, texture, NULL, &renderBox);
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
int Texture::getCenterX()
{
    return this->getWidth() / 2;
}
int Texture::getCenterY()
{
    return this->getHeight() / 2;
}
int Texture::getId(){
    return this->id;
}