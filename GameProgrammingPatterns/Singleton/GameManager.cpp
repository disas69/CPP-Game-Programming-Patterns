#include "GameManager.h"
#include <iostream>

void GameManager::Initialize()
{
    std::cout << "GameManager::Initialize()" << std::endl;
    
    StateMachine.AddTransition(GameState::None, GameState::Start, []() { std::cout << "Start Game" << std::endl; });
    StateMachine.AddTransition(GameState::Start, GameState::Update, []() { std::cout << "Update Game" << std::endl; });
    StateMachine.AddTransition(GameState::Update, GameState::Shutdown, []() { std::cout << "Shutdown Game" << std::endl; });
}

void GameManager::Start()
{
    StateMachine.SetState(GameState::Start);
}

void GameManager::Update()
{
    StateMachine.SetState(GameState::Update);
}

void GameManager::Shutdown()
{
    StateMachine.SetState(GameState::Shutdown);
}

GameManager::~GameManager()
{
    std::cout << "GameManager::~GameManager()" << std::endl;
}