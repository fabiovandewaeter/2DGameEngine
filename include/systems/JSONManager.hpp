#ifndef json_manager_hpp
#define json_manager_hpp

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

class JSONManager
{
public:
    JSONManager();
    ~JSONManager();

    static rapidjson::Document loadFile(std::string file_name);

private:
};

#endif
