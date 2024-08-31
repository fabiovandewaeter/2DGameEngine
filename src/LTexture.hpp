#ifndef ltexture_hpp
#define ltexture_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// source : https://lazyfoo.net/tutorials/SDL/10_color_keying/index.php
//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile(const char *path, SDL_Renderer *renderer);

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render( int x, int y, SDL_Renderer *renderer);

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture *mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

#endif