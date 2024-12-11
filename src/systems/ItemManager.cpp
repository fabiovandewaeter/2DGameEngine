#include "systems/ItemManager.hpp"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "items/Resource.hpp"
#include "items/Item.hpp"

ItemManager::ItemManager() {}
ItemManager::~ItemManager() {}

void ItemManager::free()
{
    int size = this->resources.size();
    for (int i = 0; i < size; i++)
    {
        delete this->resources[i];
    }
}

void ItemManager::init() {}
void ItemManager::load()
{
    FILE* file = fopen("data/resources.json", "r");
    if (!file)
    {
        std::cerr << "Failed to open data/resources.json" << std::endl;
        return;
    }

    char buffer[65536];
    rapidjson::FileReadStream inputStream(file, buffer, sizeof(buffer));
    rapidjson::Document resourcesData;

    if (resourcesData.ParseStream(inputStream).HasParseError())
    {
        std::cerr << "Error parsing data/resources.json" << std::endl;
        fclose(file);
        return;
    }
    fclose(file);

    loadResources(resourcesData);
    loadItems(resourcesData);
}

void ItemManager::genericLoader(const rapidjson::Document& resourcesData, const std::string type, const std::vector<std::string>& requiredFields, std::vector<std::string>& results)
{
    if (!resourcesData.HasMember(type.c_str()) || !resourcesData[type.c_str()].IsArray())
    {
        std::cerr << "Invalid or missing " << type << " array in JSON" << std::endl;
        return;
    }

    int sizeRequiredFields = requiredFields.size();
    const auto& resourcesArray = resourcesData["resources"].GetArray();
    for (rapidjson::SizeType i = 0; i < resourcesArray.Size(); ++i)
    {
        const auto& resource = resourcesArray[i];
        bool allRequiredFieldsPresent = true;

        for (int i = 0; i < sizeRequiredFields; i++) {
            std::string field = requiredFields[i];
            if (!resource.HasMember(field.c_str())) {
                allRequiredFieldsPresent = false;
                std::cerr << "Missing " << field << " in a resource entry" << std::endl;
                break;
            }
            else{
                results.push_back(resource[field.c_str()].GetString());
                std::cout << results[results.size()-1].c_str() << std::endl;
            }
        }
    }
}

void ItemManager::loadResources(const rapidjson::Document& resourcesData)
{
    std::vector<std::string> requiredFields;
    requiredFields.push_back("name");
    requiredFields.push_back("type");
    std::vector<std::string> results;
    genericLoader(resourcesData, "resources", requiredFields, results);
    /*if (!resourcesData.HasMember("resources") || !resourcesData["resources"].IsArray())
    {
        std::cerr << "Invalid or missing 'resources' array in JSON" << std::endl;
        return;
    }

    const auto& resourcesArray = resourcesData["resources"].GetArray();
    for (rapidjson::SizeType i = 0; i < resourcesArray.Size(); ++i)
    {
        const auto& resource = resourcesArray[i];
        if (!resource.HasMember("name") || !resource.HasMember("type"))
        {
            std::cerr << "Missing 'name' or 'type' in a resource entry" << std::endl;
            continue;
        }

        std::string name = resource["name"].GetString();
        std::string type = resource["type"].GetString();

        Resource* newResource = new Resource(name, nullptr);
        this->resources.push_back(newResource);
        std::cout << name << std::endl;
    }*/
}

void ItemManager::loadItems(const rapidjson::Document& resourcesData)
{
    if (!resourcesData.HasMember("items") || !resourcesData["items"].IsArray())
    {
        std::cerr << "Invalid or missing 'items' array in JSON" << std::endl;
        return;
    }

    const auto& itemsArray = resourcesData["items"].GetArray();
    for (rapidjson::SizeType i = 0; i < itemsArray.Size(); ++i)
    {
        const auto& item = itemsArray[i];
        if (!item.HasMember("name") || !item.HasMember("type"))
        {
            std::cerr << "Missing 'name' or 'type' in an item entry" << std::endl;
            continue;
        }

        std::string name = item["name"].GetString();
        std::string type = item["type"].GetString();

        Item* newItem = new Item(name, nullptr);
        this->items.push_back(newItem);
        std::cout << name << std::endl;
    }
}


std::vector<Item*>* ItemManager::getItems() { return &this->items; }
std::vector<Resource*>* ItemManager::getResources() { return &this->resources; }
