#include "systems/core/AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager() {}
AudioManager::~AudioManager() {}
void AudioManager::free()
{
    int size = musics.size();
    for (int i = 0; i < size; i++)
    {
        Mix_FreeMusic(musics[i]);
        musics[i] = NULL;
    }
}

void AudioManager::init()
{
}
void AudioManager::loadMedia()
{
    /*music.push_back(Mix_LoadMUS("assets/audio/music/Evangelion.wav"));
    Mix_PlayMusic(music[0], -1);*/
}

std::vector<Mix_Music *> *AudioManager::getMusics()
{
    return &musics;
}