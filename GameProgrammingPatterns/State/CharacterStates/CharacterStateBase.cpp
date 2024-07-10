#include "CharacterStateBase.h"

CharacterStateBase::CharacterStateBase(Character* Owner)
{
    OwnerCharacter = Owner;
}

void CharacterStateBase::Enter() {}
void CharacterStateBase::Exit() {}
void CharacterStateBase::Update(float DeltaTime) {}
void CharacterStateBase::HandleInput(InputType Input) {}