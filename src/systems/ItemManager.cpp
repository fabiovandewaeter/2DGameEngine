#include "systems/ItemManager.hpp"

#include "json.hpp"
#include <nlohmann/json.hpp>
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
    std::ifstream file("data/resources.json");
    if (!file.is_open())
    {
        std::cerr << "Failed to open data/resources.json" << std::endl;
        return;
    }

    nlohmann::json_abi_v3_11_2::json resourcesData;
    file >> resourcesData;
    file.close();

    loadResources(resourcesData);
    loadItems(resourcesData);
}
void ItemManager::loadResources(nlohmann::json_abi_v3_11_2::json resourcesData)
{
    for (const auto &resource : resourcesData["resources"])
    {
        std::string name = resource["name"];
        std::string type = resource["type"];

        Resource *newResource = new Resource(name, nullptr);
        this->resources.push_back(newResource);
        std::cout << name << std::endl;
    }
}
void ItemManager::loadItems(nlohmann::json_abi_v3_11_2::json resourcesData)
{
    for (const auto &resource : resourcesData["items"])
    {
        std::string name = resource["name"];
        std::string type = resource["type"];

        Item *newItem = new Item(name, nullptr);
        this->items.push_back(newItem);
        std::cout << name << std::endl;
    }
}

std::vector<Item *> *ItemManager::getItems() { return &this->items; }
std::vector<Resource *> *ItemManager::getResources() { return &this->resources; }
