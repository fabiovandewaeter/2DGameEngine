#include "systems/game_objects/StructureFactory.hpp"

StructureFactory::StructureFactory() {}
StructureFactory::~StructureFactory() {}

void StructureFactory::registerClass(const std::string className, std::function<Structure *()> constructor)
{
    this->registry[className] = constructor;
}
Structure *StructureFactory::create(std::string className)
{
    if (this->registry.find(className) != this->registry.end())
        return this->registry[className]();
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
