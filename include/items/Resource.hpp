#ifndef resource_hpp
#define resource_hpp

#include <string>

class Texture;

class Resource
{
public:
    Resource(std::string name, Texture *texture);
    ~Resource();

private:
    std::string name;
    Texture *texture;
};

#endif