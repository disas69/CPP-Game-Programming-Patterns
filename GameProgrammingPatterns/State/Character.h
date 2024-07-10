#pragma once

#include "CharacterState.h"
#include "StateController.h"

class Character
{
public:
    Character();

    void Start();
    void Update(float DeltaTime);
    void HandleInput(InputType Input);
    void SetState(CharacterState State);

private:
    StateController<CharacterState> Controller;
};
