#include "LTexture.hpp"

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    width = 0;
    height = 0;
}
LTexture::~LTexture()
{
    //Deallocate
    free();
}
void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        width = 0;
        height = 0;
    }
}

bool LTexture::loadFromFile(const char *path, SDL_Renderer *renderer)
{
    //Get rid of preexisting texture
    free();
    // The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::render( int x, int y, SDL_Renderer *renderer)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };
    SDL_RenderCopy( renderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth()
{
    return width;
}
int LTexture::getHeight()
{
    return height;
}
void LTexture::setSize(int width, int height){
    this->width = width;
    this->height = height;
}