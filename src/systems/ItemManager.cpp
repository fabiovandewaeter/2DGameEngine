#include "systems/ItemManager.hpp"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "items/Item.hpp"
#include "items/Equipment.hpp"
#include "items/Resource.hpp"

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
        Equipment *newEquipment = new Equipment(results[i], nullptr, 0);
        this->equipments.push_back(newEquipment);
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
        Resource *newResource = new Resource(results[i], nullptr, 0);
        this->resources.push_back(newResource);
        this->allItems[results[i]] = newResource;
        std::cout << "Resource loaded : " << results[i] << std::endl;
    }
}

std::vector<Equipment *> *ItemManager::getEquipments() { return &this->equipments; }
std::vector<Resource *> *ItemManager::getResources() { return &this->resources; }
