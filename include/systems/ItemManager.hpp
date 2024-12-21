#ifndef ITEM_MANAGER_HPP
#define ITEM_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <rapidjson/document.h>

class Item;
class Resource;

// Manages the loading and management of items and resources defined in JSON files
class ItemManager
{
public:
    ItemManager();
    ~ItemManager();
    void free();

    void init();
    void load();

    std::vector<Item *> *getItems();
    std::vector<Resource *> *getResources();

private:
    std::vector<Item *> items;
    std::vector<Resource *> resources;

    int genericLoader(rapidjson::Document resourcesData, std::string type, std::vector<std::string> requiredFields, std::vector<std::string> results);
    void loadResources(rapidjson::Document resourcesData);
    void loadItems(rapidjson::Document resourcesData);
};

#endif
