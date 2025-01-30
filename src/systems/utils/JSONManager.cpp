#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#include "systems/utils/JSONManager.hpp"

#include <iostream>

JSONManager::JSONManager() {}
JSONManager::~JSONManager() {}

rapidjson::Document JSONManager::loadFile(std::string file_name)
{
#ifdef PROFILER
    ZoneScoped;
#endif
    rapidjson::Document itemsData;
    FILE *file = fopen(file_name.c_str(), "r");
    if (!file)
    {
        std::cerr << "Failed to open data/resources.json" << std::endl;
        return itemsData;
    }

    char buffer[65536];
    rapidjson::FileReadStream inputStream(file, buffer, sizeof(buffer));

    if (itemsData.ParseStream(inputStream).HasParseError())
    {
        std::cerr << "Error parsing file:" << file_name << std::endl;
        fclose(file);
        return itemsData;
    }
    fclose(file);

    return itemsData;
}
