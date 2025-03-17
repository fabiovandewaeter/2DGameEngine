#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "systems/game_objects/ItemFactory.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>

#include "items/Item.hpp"
#include "systems/utils/JSONManager.hpp"

ItemFactory::ItemFactory() {}

ItemFactory::~ItemFactory()
{
    for (auto &pair : allItems)
    {
        delete pair.second;
    }
}

void ItemFactory::free()
{
    for (auto &pair : allItems)
    {
        delete pair.second;
    }
    allItems.clear();
}

void ItemFactory::init() {}
void ItemFactory::load()
{
    loadEquipments("data/equipments.json");
    loadResources("data/resources.json");
}

std::unordered_map<std::string, Item *> ItemFactory::allItems;
Item *ItemFactory::getItem(std::string name)
{
    if (allItems.empty())
    {
        std::cerr << "Error: allItems is not initialized." << std::endl;
        return nullptr;
    }
    auto item = allItems.find(name);
    if (item != allItems.end())
    {
        return item->second;
    }
    std::cout << "Item not found : " << name << std::endl;
    return nullptr;
}

int ItemFactory::genericLoader(std::string file_name, std::string type, std::vector<std::string> &requiredFields, std::vector<std::string> &results)
{
    rapidjson::Document itemsData = JSONManager::loadFile(file_name);

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

        for (int i = 0; i < sizeRequiredFields; i++)
        {
            std::string field = requiredFields[i];
            if (!item.HasMember(field.c_str()))
            {
                std::cerr << "File: " << file_name << " | Missing " << field << " in a item entry" << std::endl;
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

void ItemFactory::loadEquipments(std::string file_name)
{
    std::vector<std::string> requiredFields;
    requiredFields.push_back("name");
    std::vector<std::string> results;
    int quantityFound = genericLoader(file_name, "equipments", requiredFields, results);

    int numberOfFields = requiredFields.size();
    for (int i = 0; i < quantityFound; i += numberOfFields)
    {
        Item *newEquipment = new Item(results[i], nullptr, 0, true);
        allItems[results[i]] = newEquipment;
        std::cout << "Equipment loaded: " << results[i] << std::endl;
    }
}
void ItemFactory::loadResources(std::string file_name)
{
    std::vector<std::string> requiredFields;
    requiredFields.push_back("name");
    std::vector<std::string> results;
    int quantityFound = genericLoader(file_name, "resources", requiredFields, results);

    int numberOfFields = requiredFields.size();
    for (int i = 0; i < quantityFound; i += numberOfFields)
    {
        Item *newResource = new Item(results[i], nullptr, 0, false);
        allItems[results[i]] = newResource;
        std::cout << "Resource loaded: " << results[i] << std::endl;
    }
}
