#ifndef item_manager_hpp
#define item_manager_hpp

#include <vector>
#include <unordered_map>
#include <string>

class Item;
class Resource;

// load all resources defined in JSON files

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

    void loadResources(nlohmann::json_abi_v3_11_2::json resourcesData);
    void loadItems(nlohmann::json_abi_v3_11_2::json resourcesData);
};

#endif