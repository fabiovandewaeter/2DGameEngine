#include "systems/ItemManager.hpp"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "items/Item.hpp"

ItemManager::ItemManager() {}
ItemManager::~ItemManager() {}

void ItemManager::free()
{
    for (auto &pair : this->allItems)
    {
        delete pair.second;
    }
    this->allItems.clear();
}

void ItemManager::init() {}
void ItemManager::load()
{
    loadEquipments("data/equipments.json");
    loadResources("data/resources.json");
}

rapidjson::Document ItemManager::loadItemFile(std::string file_name)
{
    FILE *file = fopen(file_name.c_str(), "r");
    if (!file)
    {
        std::cerr << "Failed to open data/resources.json" << std::endl;
        return nullptr;
    }

    char buffer[65536];
    rapidjson::FileReadStream inputStream(file, buffer, sizeof(buffer));
    rapidjson::Document itemsData;

    if (itemsData.ParseStream(inputStream).HasParseError())
    {
        std::cerr << "Error parsing data/resources.json" << std::endl;
        fclose(file);
        return nullptr;
    }
    fclose(file);

    return itemsData;
}
int ItemManager::genericLoader(std::string file_name, std::string type, std::vector<std::string> &requiredFields, std::vector<std::string> &results)
{
    rapidjson::Document itemsData = loadItemFile(file_name);

    if (!itemsData.HasMember(type.c_str()) || !itemsData[type.c_str()].IsArray())
    {
        std::cerr << "Invalid or missing " << type << " array in JSON" << std::endl;
        return 0;
    }

    int quantityFound = 0;
    int sizeRequiredFields = requiredFields.size();
    const auto &itemsArray = itemsData[type.c_str()].GetArray();
    for (rapidjson::SizeType i = 0; i < itemsArray.Size(); ++i)
    {
        const auto &item = itemsArray[i];
        bool allRequiredFieldsPresent = true;

        for (int i = 0; i < sizeRequiredFields; i++)
        {
            std::string field = requiredFields[i];
            if (!item.HasMember(field.c_str()))
            {
                allRequiredFieldsPresent = false;
                std::cerr << "File : " << file_name << " | Missing " << field << " in a item entry" << std::endl;
                break;
            }
            else
            {
                quantityFound++;
                results.push_back(item[field.c_str()].GetString());
            }
        }
    }
    return quantityFound;
}

void ItemManager::loadEquipments(std::string file_name)
{
    std::vector<std::string> requiredFields;
    requiredFields.push_back("name");
    std::vector<std::string> results;
    int quantityFound = genericLoader(file_name, "equipments", requiredFields, results);

    int numberOfFields = requiredFields.size();
    for (int i = 0; i < quantityFound; i += numberOfFields)
    {
        Item *newEquipment = new Item(results[i], nullptr, 0, true);
        this->allItems[results[i]] = newEquipment;
        std::cout << "Equipment loaded : " << results[i] << std::endl;
    }
}
void ItemManager::loadResources(std::string file_name)
{
    std::vector<std::string> requiredFields;
    requiredFields.push_back("name");
    std::vector<std::string> results;
    int quantityFound = genericLoader(file_name, "resources", requiredFields, results);

    int numberOfFields = requiredFields.size();
    for (int i = 0; i < quantityFound; i += numberOfFields)
    {
        Item *newResource = new Item(results[i], nullptr, 0, false);
        this->allItems[results[i]] = newResource;
        std::cout << "Resource loaded : " << results[i] << std::endl;
    }
}
