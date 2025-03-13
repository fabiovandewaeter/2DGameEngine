#include "Texture.hpp"

#include "systems/core/Camera.hpp"

int Texture::idCounter = 0;

Texture::Texture(Camera *camera, std::string path) : texture(NULL), camera(camera), renderer(camera->getRenderer()), width(0), height(0), id(idCounter)
{
    loadFromFile(path);
    idCounter++;
}

Texture::~Texture() { free(); }

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

Texture *Texture::loadFromFile(std::string path)
{
    // Get rid of preexisting texture
    free();
    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
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

Texture *Texture::loadFromRenderedText(TTF_Font *font, std::string text, SDL_Color textColor)
{
    free();
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            width = textSurface->w;
            height = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    return this;
}

SDL_Texture *Texture::getTexture() const { return texture; }
int Texture::getWidth() { return width; }
int Texture::getHeight() { return height; }
void Texture::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}
int Texture::getCenterX() { return getWidth() / 2; }
int Texture::getCenterY() { return getHeight() / 2; }
int Texture::getId() { return id; }
int Texture::getTextureDefaultSize() { return TEXTURE_DEFAULT_SIZE; }
