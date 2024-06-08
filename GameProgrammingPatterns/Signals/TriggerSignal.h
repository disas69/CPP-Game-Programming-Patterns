#pragma once

#include "Signal.h"

class TriggerSignal : public Signal<void>
{
public:
    TriggerSignal() = default;
};
