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

    void registerClass(const std::string className, std::function<Structure *(Texture *, int, int, Player *, TickManager *)> constructor);
    std::function<Structure *(Texture *, int, int, Player *, TickManager *)> getConstructor(std::string className);
    std::vector<std::string> getRegistredClasses();

    static StructureFactory &getInstance()
    {
        static StructureFactory factory;
        return factory;
    }

private:
    std::unordered_map<std::string, std::function<Structure *(Texture *, int, int, Player *, TickManager *)>> registry;
};

// to add at the end of every Structure subclasses .cpp files
#define REGISTER_CLASS(classname)                                                                                                                                             \
    static struct classname##Registrar                                                                                                                                        \
    {                                                                                                                                                                         \
        classname##Registrar()                                                                                                                                                \
        {                                                                                                                                                                     \
            StructureFactory::getInstance().registerClass(                                                                                                                    \
                #classname, [](Texture *texture, float x, float y, Player *placedBy, TickManager *tickManager) { return new classname(texture, x, y, placedBy, tickManager); }); \
        }                                                                                                                                                                     \
    } global_##classname##_registrar;

#endif
