#include "Texture.hpp"

int counter = 0;
Texture::Texture() {}
Texture::Texture(SDL_Renderer *renderer)
{
    // Initialize
    this->texture = NULL;
    this->width = 0;
    this->height = 0;
    this->renderer = renderer;
    this->id = counter;
    counter++;
}
Texture::~Texture()
{
    free();
}
void Texture::free()
{
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
        newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        else
        {
            this->width = loadedSurface->w;
            this->height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    texture = newTexture;
    return this;
}
Texture *Texture::loadFromRenderedText(TTF_Font *font, const char *text, SDL_Color textColor)
{
    free();
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        this->texture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
        if (this->texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            this->width = textSurface->w;
            this->height = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    return this;
}

void Texture::render(SDL_Rect renderBox)
{
    if (renderBox.w == -1 || renderBox.h == -1)
    {
        SDL_Rect newRenderBox = {renderBox.x, renderBox.y, this->width, this->height};
        SDL_RenderCopy(this->renderer, texture, NULL, &newRenderBox);
    }
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
int Texture::getId()
{
    return this->id;
}