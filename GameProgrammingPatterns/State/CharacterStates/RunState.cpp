#include <iostream>
#include "RunState.h"
#include "../Character.h"

void RunState::Enter()
{
    CharacterStateBase::Enter();
    std::cout << "Entering Run State" << '\n';
}

void RunState::Exit()
{
    CharacterStateBase::Exit();
    std::cout << "Exiting Run State" << '\n';
}

void RunState::Update(float DeltaTime)
{
    CharacterStateBase::Update(DeltaTime);
    std::cout << "Updating Run State" << '\n';
}

void RunState::HandleInput(InputType Input)
{
    CharacterStateBase::HandleInput(Input);

    switch (Input)
    {
        case InputType::None:
            OwnerCharacter->SetState(CharacterState::Idle);
            break;
        case InputType::MoveLeft:
            OwnerCharacter->SetState(CharacterState::Walking);
            break;
        case InputType::MoveRight:
            OwnerCharacter->SetState(CharacterState::Walking);
            break;
        case InputType::Sprint:
            break;
        case InputType::Jump:
            OwnerCharacter->SetState(CharacterState::Jumping);
            break;
        default:
            std::cout << "RunState: Invalid Input" << '\n';
            break;
    }
}