#pragma once

#include "Event.h"

class AudioEvent : public Event
{
public:
    AudioEvent(int SoundId);
    virtual void Process() override;

private:
    int SoundId = 0;

    static int LastProcessedSoundId;
};
