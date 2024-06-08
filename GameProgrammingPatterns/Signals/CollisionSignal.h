#pragma once

#include "Signal.h"

class CollisionSignal : public Signal<bool>
{
public:
    CollisionSignal(bool Data) : Signal(Data) {}
};
