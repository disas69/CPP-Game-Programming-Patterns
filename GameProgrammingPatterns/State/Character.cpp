#include "Character.h"
#include "CharacterStates/IdleState.h"
#include "CharacterStates/JumpState.h"
#include "CharacterStates/RunState.h"
#include "CharacterStates/WalkState.h"

Character::Character()
{
    Controller = StateController<CharacterState>();
    Controller.AddState(CharacterState::Idle, new IdleState(this));
    Controller.AddState(CharacterState::Walking, new WalkState(this));
    Controller.AddState(CharacterState::Running, new RunState(this));
    Controller.AddState(CharacterState::Jumping, new JumpState(this));
}

void Character::Start()
{
    Controller.SetState(CharacterState::Idle);
}

void Character::Update(float DeltaTime)
{
    Controller.Update(DeltaTime);
}

void Character::HandleInput(InputType Input)
{
    Controller.HandleInput(Input);
}

void Character::SetState(CharacterState State)
{
    Controller.SetState(State);
}