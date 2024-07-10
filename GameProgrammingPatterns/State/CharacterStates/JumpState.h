#pragma once
#include "CharacterStateBase.h"

class JumpState : public CharacterStateBase
{
public:
    explicit JumpState(Character* Owner) : CharacterStateBase(Owner) {}

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(InputType Input) override;

private:
    int FramesCount = 0;
};
