#ifndef item_manager_hpp
#define item_manager_hpp

#include <vector>
#include <unordered_map>
#include <string>

class Item;

// load all resources defined in JSON files

class ItemManager
{
public:
    ItemManager();
    ~ItemManager();
    void free();

    void init();
    void loadAllItems();

    std::vector<Item *> *getAllItems();
    std::vector<Item *> *getItems();
    std::vector<Item *> *getResources();
    std::vector<Item *> *getMineableResources();

private:
    std::unordered_map<std::string, std::vector<Item *>> allItems;

    void loadResources();
    void loadItems();
};

#endif