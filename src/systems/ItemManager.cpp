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

int ItemManager::genericLoader(const rapidjson::Document& resourcesData, const std::string type, const std::vector<std::string>& requiredFields, std::vector<std::string>& results)
{
    if (!resourcesData.HasMember(type.c_str()) || !resourcesData[type.c_str()].IsArray())
    {
        std::cerr << "Invalid or missing " << type << " array in JSON" << std::endl;
        return 0;
    }

    int quantityFound = 0;
    int sizeRequiredFields = requiredFields.size();
    const auto& resourcesArray = resourcesData[type.c_str()].GetArray();
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
                quantityFound++;
                results.push_back(resource[field.c_str()].GetString());
            }
        }
    }
    return quantityFound;
}

void ItemManager::loadResources(const rapidjson::Document& resourcesData)
{
    std::vector<std::string> requiredFields;
    requiredFields.push_back("name");
    requiredFields.push_back("type");
    std::vector<std::string> results;
    int quantityFound = genericLoader(resourcesData, "resources", requiredFields, results);

    int numberOfFields = requiredFields.size();
    for (int i = 0; i < quantityFound; i += numberOfFields){
        this->resources.push_back(new Resource(results[i], nullptr));
        std::cout << "Resource loaded : " << results[i] << std::endl;
    }
}

void ItemManager::loadItems(const rapidjson::Document& resourcesData)
{
    std::vector<std::string> requiredFields;
    requiredFields.push_back("name");
    requiredFields.push_back("type");
    std::vector<std::string> results;
    int quantityFound = genericLoader(resourcesData, "items", requiredFields, results);

    int numberOfFields = requiredFields.size();
    for (int i = 0; i < quantityFound; i += numberOfFields){
        this->items.push_back(new Item(results[i], nullptr));
        std::cout << "Item loaded : " << results[i] << std::endl;
    }
}


std::vector<Item*>* ItemManager::getItems() { return &this->items; }
std::vector<Resource*>* ItemManager::getResources() { return &this->resources; }
