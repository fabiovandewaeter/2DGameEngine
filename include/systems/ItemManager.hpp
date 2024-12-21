#ifndef ITEM_MANAGER_HPP
#define ITEM_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <rapidjson/document.h>

class Item;
class Consumable;
class Equipment;
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

    std::vector<Equipment *> *getEquipments();
    std::vector<Resource *> *getResources();
    std::unordered_map<std::string, Item *> *getAllItems();

private:
    std::vector<Equipment *> equipments;
    std::vector<Resource *> resources;
    std::unordered_map<std::string, Item *> allItems;

    rapidjson::Document loadItemFile(std::string file_name);
    int genericLoader(std::string file_name, std::string type, std::vector<std::string> &requiredFields, std::vector<std::string> &results);
    void loadEquipments(std::string file_name);
    void loadResources(std::string file_name);
};

#endif
