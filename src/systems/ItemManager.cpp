#include "systems/ItemManager.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

ItemManager::ItemManager() {}
ItemManager::~ItemManager() {}

void ItemManager::free() {}

void ItemManager::init() { loadAllItems(); }
void ItemManager::loadAllItems()
{
    loadItems();
    loadResources();
}
void ItemManager::loadResources()
{
    std::ifstream file("data/resources.json");
    if (!file.is_open())
    {
        std::cerr << "Failed to open data/resources.json" << std::endl;
        return;
    }

    json resourcesData;
    file >> resourcesData;
    file.close();

    for (const auto &resource : resourcesData["resources"])
    {
        std::string name = resource["name"];
        std::string type = resource["type"];

        Item *newItem = new Item(name, type);
        this->allItems.push_back(newItem);
    }
}
void ItemManager::loadItems()
{
    // load items from JSON
    // this->allItems["items"].add();
}

std::vector<Item *> *ItemManager::getAllItems() {}
std::vector<Item *> *ItemManager::getItems()
{ // return this->allItems["items"];
}
std::vector<Item *> *ItemManager::getResources()
{ // return this->allItems["resources"];
}
std::vector<Item *> *ItemManager::getMineableResources()
{ // return this->allItems["resources"].filter(minable);
}
