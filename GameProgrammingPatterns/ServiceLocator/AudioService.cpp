#include "AudioService.h"
#include <iostream>

void AudioService::PlaySound(std::string SoundID)
{
    std::cout << "AudioService::PlaySound(" << SoundID << ")" << std::endl;
}

void AudioService::StopSound(std::string SoundID)
{
    std::cout << "AudioService::StopSound(" << SoundID << ")" << std::endl;
}