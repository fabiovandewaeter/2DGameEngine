#ifndef io_manager_hpp
#define io_manager_hpp

#define TOTAL_DATA 1000

#include <SDL_stdinc.h>


class IOManager
{
public:
    IOManager();
    ~IOManager();
private:
    Sint32 data[TOTAL_DATA];
};

#endif