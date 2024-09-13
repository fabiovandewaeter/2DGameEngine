#include "TextManager.hpp"

TextManager::TextManager(){}
TextManager::~TextManager(){}

void TextManager::init(){
    loadAllCharactersTextures();
}

void TextManager::loadAllCharactersTextures(){

}

Texture *TextManager::generateTextTexture(std::string text){
    int size = text.size();
    for (int i = 0; i < size; i ++){
        char c = text[i];
        if ((c >= 32) && (c <= 126) ){
            int textureIndex = c - 32;

        }
    }
}