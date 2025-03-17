#ifndef item_manager_hpp
#define item_manager_hpp

#include <vector>
#include <unordered_map>
#include <string>
#include <rapidjson/document.h>

class Item;
class Consumable;
class Equipment;
class Resource;

// Manages the loading and management of items and resources defined in JSON files
class ItemFactory
{
public:
    ItemFactory();
    ~ItemFactory();
    void free();

    void init();
    void load();

    static Item *getItem(std::string name);

private:
    static std::unordered_map<std::string, Item *> allItems;

    int genericLoader(std::string file_name, std::string type, std::vector<std::string> &requiredFields, std::vector<std::string> &results);
    void loadEquipments(std::string file_name);
    void loadResources(std::string file_name);
};

#endif
