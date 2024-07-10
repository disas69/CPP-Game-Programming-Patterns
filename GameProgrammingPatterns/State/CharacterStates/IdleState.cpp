#include <iostream>
#include "IdleState.h"
#include "../Character.h"
#include "../CharacterState.h"

void IdleState::Enter()
{
    CharacterStateBase::Enter();
    std::cout << "Entering Idle State" << '\n';
}

void IdleState::Exit()
{
    CharacterStateBase::Exit();
    std::cout << "Exiting Idle State" << '\n';
}

void IdleState::Update(float DeltaTime)
{
    CharacterStateBase::Update(DeltaTime);
    std::cout << "Updating Idle State" << '\n';
}

void IdleState::HandleInput(InputType Input)
{
    CharacterStateBase::HandleInput(Input);
    
    switch (Input)
    {
        case InputType::None:
            break;
        case InputType::MoveLeft:
            OwnerCharacter->SetState(CharacterState::Walking);
            break;
        case InputType::MoveRight:
            OwnerCharacter->SetState(CharacterState::Walking);
            break;
        case InputType::Sprint:
            OwnerCharacter->SetState(CharacterState::Running);
            break;
        case InputType::Jump:
            OwnerCharacter->SetState(CharacterState::Jumping);
            break;
        default:
            std::cout << "IdleState: Invalid Input" << '\n';
            break;
    }
}