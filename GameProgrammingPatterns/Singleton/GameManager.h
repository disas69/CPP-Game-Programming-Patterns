#pragma once

#include "Singleton.h"
#include "../StateMachine/StateMachine.h"

enum class GameState : int
{
    None,
    Start,
    Update,
    Shutdown
};

class GameManager : public Singleton<GameManager>
{
public:
    GameManager() : StateMachine(GameState::None)
    {
        Initialize();
    }

    ~GameManager() override;

    void Initialize();
    void Start();
    void Update();
    void Shutdown();

private:
    StateMachine<GameState> StateMachine;
};
