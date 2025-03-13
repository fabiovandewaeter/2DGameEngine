#ifndef audio_manager_hpp
#define audio_manager_hpp

#include <vector>
#include <SDL2/SDL_mixer.h>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();
    void free();

    void init();
    void loadMedia();

    std::vector<Mix_Music *> *getMusics();

private:
    std::vector<Mix_Music *> musics;
};

#endif
