#ifndef text_manager_hpp
#define text_manager_hpp

#define NUMBER_OF_CHARACTERS 94

#include "../Texture.hpp"

// generate text
class TextManager
{
public:
    TextManager();
    ~TextManager();
    
    void init();
    void loadAllCharactersTextures();
    
    Texture *generateTextTexture(const char* text);
private:
    Texture *allCharacterTextures[NUMBER_OF_CHARACTERS];
};

#endif