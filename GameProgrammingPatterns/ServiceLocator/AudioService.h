#pragma once

#include <string>

class AudioService
{
public:
    void PlaySound(std::string SoundID);
    void StopSound(std::string SoundID);
};
