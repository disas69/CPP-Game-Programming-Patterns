#include <iostream>
#include "AudioEvent.h"

int AudioEvent::LastProcessedSoundId = -1;

AudioEvent::AudioEvent(int SoundId)
{
    this->SoundId = SoundId;
}

void AudioEvent::Process()
{
    if (SoundId == LastProcessedSoundId)
    {
        std::cout << "Ignoring duplicate sound with ID " << SoundId << std::endl;
        return;
    }
    
    std::cout << "Playing sound with ID " << SoundId << std::endl;
    LastProcessedSoundId = SoundId;
}