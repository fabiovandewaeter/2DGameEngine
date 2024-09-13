#ifndef text_manager_hpp
#define text_manager_hpp

#define NUMBER_OF_CHARACTERS 94

#include <SDL_ttf.h>
#include "../Texture.hpp"

// generate text
class TextManager
{
public:
    TextManager();
    ~TextManager();

    void init();
    void loadAllCharactersTextures();

    Texture *generateTextTexture(std::string text);

private:
    Texture *allCharacterTextures[NUMBER_OF_CHARACTERS];
    TTF_Font *font;
};

#endif