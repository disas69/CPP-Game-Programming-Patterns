#include <iostream>
#include <vector>

#include "ObjectPool/ObjectPool.h"
#include "ObjectPool/PooledEntity.h"
#include "Singleton/GameManager.h"
#include "StateMachine/StateMachine.h"

void ObjectPoolTest()
{
    ObjectPool<PooledEntity> Pool(3);

    std::vector<std::shared_ptr<PooledEntity>> Entities;
    for (size_t i = 0; i < 5; ++i)
    {
        std::shared_ptr<PooledEntity> Entity = Pool.GetObject();
        Entity->SetPosition(i, i * 2);

        std::cout << "Entity position: " << Entity->GetXPosition() << ", " << Entity->GetYPosition() << std::endl;
        Entities.push_back(Entity);
    }

    for (const auto& Entity : Entities)
    {
        Pool.ReturnObject(Entity);
    }
    Entities.clear();
}

void StateMachineTest()
{
    enum class State : int
    {
        Idle,
        Walking,
        Running
    };

    StateMachine<State> StateMachine(State::Idle);
    StateMachine.AddTransition(State::Idle, State::Walking, []() { std::cout << "Start Walking" << std::endl; });
    StateMachine.AddTransition(State::Walking, State::Running, []() { std::cout << "Start Running" << std::endl; });
    StateMachine.AddTransition(State::Running, State::Idle, []() { std::cout << "Start Idle" << std::endl; });

    StateMachine.SetState(State::Walking);
    StateMachine.SetState(State::Running);
    StateMachine.SetState(State::Idle);
}

void SingletonTest()
{
    GameManager::GetInstance().Start();
    GameManager::GetInstance().Update();
    GameManager::GetInstance().Shutdown();
}

int main(int argc, char* argv[])
{
    // ObjectPoolTest();

    // StateMachineTest();

    SingletonTest();
    
    return 0;
}
