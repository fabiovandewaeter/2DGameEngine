#ifndef structure_factory_hpp
#define structure_factory_hpp

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <vector>

#include "structures/Structure.hpp"

class TickManager;

class StructureFactory
{
public:
    StructureFactory();
    ~StructureFactory();

    void registerClass(const std::string className, std::function<Structure *(std::string , float, float, Player *, TickManager *)> constructor);
    std::function<Structure *(std::string , float, float, Player *, TickManager *)> getConstructor(std::string className);
    std::vector<std::string> getRegistredClasses();

    static StructureFactory &getInstance()
    {
        static StructureFactory factory;
        return factory;
    }

private:
    std::unordered_map<std::string, std::function<Structure *(std::string , float, float, Player *, TickManager *)>> registry;
};

// to add at the end of every Structure subclasses .cpp files
#define REGISTER_CLASS(classname)                                                                                                                                                \
    static struct classname##Registrar                                                                                                                                           \
    {                                                                                                                                                                            \
        classname##Registrar()                                                                                                                                                   \
        {                                                                                                                                                                        \
            StructureFactory::getInstance().registerClass(                                                                                                                       \
                #classname, [](std::string textureName, float x, float y, Player *placedBy, TickManager *tickManager) { return new classname(textureName, x, y, placedBy, tickManager); }); \
        }                                                                                                                                                                        \
    } global_##classname##_registrar;

#endif
