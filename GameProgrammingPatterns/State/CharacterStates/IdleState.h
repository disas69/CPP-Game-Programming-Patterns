#pragma once

#include "../State.h"
#include "CharacterStateBase.h"

class Character;

class IdleState : public CharacterStateBase
{
public:
    explicit IdleState(Character* Owner) : CharacterStateBase(Owner) {}

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(InputType Input) override;
};
