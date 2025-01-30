#include "systems/core/TextureManager.hpp"

#include "Texture.hpp"
#include "systems/utils/JSONManager.hpp"

TextureManager::TextureManager() {}
TextureManager::TextureManager(SDL_Renderer *renderer) { init(renderer); }
TextureManager::~TextureManager() {}

void TextureManager::init(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    loadConfiguration();
}
void TextureManager::loadConfiguration()
{
    rapidjson::Document document = JSONManager::loadFile("data/configurations/TextureManagerConfiguration.json");

    const char *categories[] = {"UTILS", "structureTextures", "tileTextures", "entityTextures"};
    for (const char *category : categories)
    {
        if (document.HasMember(category) && document[category].IsArray())
        {
            for (const auto &textureData : document[category].GetArray())
            {
                if (textureData.HasMember("path") && textureData["path"].IsString())
                {
                    std::string texturePath = textureData["path"].GetString();
                    std::cout << "Load texture: " << texturePath << std::endl;
                    this->textures[textureData["name"].GetString()] = new Texture(this->renderer, texturePath);
                }
            }
        }
    }
}
Texture *TextureManager::getTexture(std::string name)
{
    auto it = this->textures.find(name);
    if (it != textures.end())
    {
        return it->second;
    }
    return this->textures["DEFAULT"];
}
