#include "systems/core/TextureManager.hpp"

#include "Texture.hpp"
#include "systems/utils/JSONManager.hpp"

TextureManager::~TextureManager() {}

void TextureManager::loadConfiguration()
{
    rapidjson::Document document = JSONManager::loadFile("data/configurations/TextureManagerConfiguration.json");

    const char *categories[] = {"UTILS", "GUI", "structureTextures", "tileTextures", "entityTextures"};
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
                    textures[textureData["name"].GetString()] = new Texture(camera, texturePath);
                }
            }
        }
    }
}

Texture *TextureManager::getTexture(std::string name)
{
    auto it = textures.find(name);
    if (it != textures.end())
    {
        return it->second;
    }
    return textures["DEFAULT"];
}
