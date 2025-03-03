#include "systems/game_objects/StructureFactory.hpp"

StructureFactory::StructureFactory() {}
StructureFactory::~StructureFactory() {}

void StructureFactory::registerClass(const std::string className, std::function<Structure *(Texture *, float, float, Player *, TickManager *)> constructor)
{
    this->registry[className] = constructor;
}

std::function<Structure *(Texture *, float, float, Player *, TickManager *)> StructureFactory::getConstructor(std::string className)
{
    auto it = this->registry.find(className);
    if (it != this->registry.end())
    {
        return it->second;
    }
    return nullptr;
}
std::vector<std::string> StructureFactory::getRegistredClasses()
{
    std::vector<std::string> keys;
    for (const auto &pair : this->registry)
    {
        keys.push_back(pair.first);
    }
    return keys;
}
