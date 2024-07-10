#include <iostream>
#include "JumpState.h"
#include "../Character.h"

void JumpState::Enter()
{
    CharacterStateBase::Enter();
    std::cout << "Entering Jump State" << '\n';
    FramesCount = 0;
}

void JumpState::Exit()
{
    CharacterStateBase::Exit();
    std::cout << "Exiting Jump State" << '\n';
}

void JumpState::Update(float DeltaTime)
{
    CharacterStateBase::Update(DeltaTime);
    std::cout << "Updating Jump State" << '\n';

    if (FramesCount >= 2)
    {
        OwnerCharacter->SetState(CharacterState::Idle);
    }
    else
    {
        FramesCount++;
    }
}

void JumpState::HandleInput(InputType Input)
{
    CharacterStateBase::HandleInput(Input);
}