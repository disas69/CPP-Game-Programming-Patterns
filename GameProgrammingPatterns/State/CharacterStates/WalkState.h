#pragma once

#include "CharacterStateBase.h"
#include "../State.h"

class Character;

class WalkState : public CharacterStateBase
{
public:
    explicit WalkState(Character* Owner) : CharacterStateBase(Owner) {}

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(InputType Input) override;
};
