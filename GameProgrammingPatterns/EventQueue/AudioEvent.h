#pragma once

#include "Event.h"

class AudioEvent : public Event
{
public:
    static int LastProcessedSoundId;

    AudioEvent(int SoundId);
    virtual void Process() override;

private:
    int SoundId = 0;
};
