#include <iostream>
#include "WalkState.h"
#include "../Character.h"

void WalkState::Enter()
{
    CharacterStateBase::Enter();
    std::cout << "Entering Walk State" << '\n';
}

void WalkState::Exit()
{
    CharacterStateBase::Exit();
    std::cout << "Exiting Walk State" << '\n';
}

void WalkState::Update(float DeltaTime)
{
    CharacterStateBase::Update(DeltaTime);
    std::cout << "Updating Walk State" << '\n';
}

void WalkState::HandleInput(InputType Input)
{
    CharacterStateBase::HandleInput(Input);

    switch (Input)
    {
        case InputType::None:
            OwnerCharacter->SetState(CharacterState::Idle);
            break;
        case InputType::MoveLeft:
            break;
        case InputType::MoveRight:
            break;
        case InputType::Sprint:
            OwnerCharacter->SetState(CharacterState::Running);
            break;
        case InputType::Jump:
            OwnerCharacter->SetState(CharacterState::Jumping);
            break;
        default:
            std::cout << "WalkState: Invalid Input" << '\n';
            break;
    }
}