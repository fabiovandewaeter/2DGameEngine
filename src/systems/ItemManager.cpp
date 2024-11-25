#include "systems/ItemManager.hpp"

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
    // load ressources from JSON
    // this->allItems["resources"].add();
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
