#ifndef texture_hpp
#define texture_hpp

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "systems/utils/Constants.hpp"

class Camera;

// source : https://lazyfoo.net/tutorials/SDL/10_color_keying/index.php
// Texture wrapper class
class Texture
{
public:
    Texture();
    // Texture are liked to one SDL_Renderer
    Texture(Camera *camera, std::string path);
    ~Texture();
    void free();

    SDL_Texture *getTexture();
    int getWidth();
    int getHeight();
    void setSize(int width, int height);
    int getCenterX();
    int getCenterY();
    int getId();
    int getTextureDefaultSize();

private:
    SDL_Texture *texture;
    Camera *camera;
    SDL_Renderer *renderer;
    int width, height;
    int id;

    Texture *loadFromFile(std::string path);
    Texture *loadFromRenderedText(TTF_Font *font, std::string text, SDL_Color textColor);
};

#endif
