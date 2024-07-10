#pragma once

#include "InputType.h"

class State
{
public:
    State() = default;
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    virtual ~State() = default;
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update(float DeltaTime) = 0;
    virtual void HandleInput(InputType Input) = 0;
};
