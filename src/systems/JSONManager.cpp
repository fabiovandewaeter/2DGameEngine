#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "systems/JSONManager.hpp"

#include <iostream>

JSONManager::JSONManager() {}
JSONManager::~JSONManager() {}

rapidjson::Document JSONManager::loadFile(std::string file_name)
{
#ifdef PROFILER
    ZoneScoped;
#endif
    FILE *file = fopen(file_name.c_str(), "r");
    if (!file)
    {
        std::cerr << "Failed to open data/resources.json" << std::endl;
        return nullptr;
    }

    char buffer[65536];
    rapidjson::FileReadStream inputStream(file, buffer, sizeof(buffer));
    rapidjson::Document itemsData;

    if (itemsData.ParseStream(inputStream).HasParseError())
    {
        std::cerr << "Error parsing data/resources.json" << std::endl;
        fclose(file);
        return nullptr;
    }
    fclose(file);

    return itemsData;
}
