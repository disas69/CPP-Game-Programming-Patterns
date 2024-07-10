#pragma once

#include "../State.h"

class Character;

class CharacterStateBase : public State
{
public:
    CharacterStateBase(Character* Owner);
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(InputType Input) override;

protected:
    Character* OwnerCharacter = nullptr;
};
