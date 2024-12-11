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

    int genericLoader(const rapidjson::Document& resourcesData, const std::string type, const std::vector<std::string>& requiredFields, std::vector<std::string>& results);
    void loadResources(const rapidjson::Document& resourcesData);
    void loadItems(const rapidjson::Document& resourcesData);
};

#endif
