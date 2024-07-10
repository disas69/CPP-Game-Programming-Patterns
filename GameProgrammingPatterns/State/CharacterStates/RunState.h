#pragma once

#include "CharacterStateBase.h"

class RunState : public CharacterStateBase
{
public:
    explicit RunState(Character* Owner) : CharacterStateBase(Owner) {}

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(InputType Input) override;
};
