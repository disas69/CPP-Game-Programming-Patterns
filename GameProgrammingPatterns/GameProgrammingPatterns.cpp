#include <iostream>
#include <vector>
#include <memory>

#include "Command/ActionCommand.h"
#include "Command/CommandQueue.h"
#include "Command/CommandStack.h"
#include "ObjectPool/ObjectPool.h"
#include "ObjectPool/PooledEntity.h"
#include "ServiceLocator/AudioService.h"
#include "ServiceLocator/ServiceLocator.h"
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

void CommandTest()
{
    ActionCommand MoveCommand([]() { std::cout << "Move" << std::endl; }, []() { std::cout << "Undo Move" << std::endl; });
    ActionCommand JumpCommand([]() { std::cout << "Jump" << std::endl; }, []() { std::cout << "Undo Jump" << std::endl; });
    ActionCommand AttackCommand([]() { std::cout << "Attack" << std::endl; }, []() { std::cout << "Undo Attack" << std::endl; });

    CommandQueue CommandQueue;
    CommandQueue.AddCommand(std::make_shared<ActionCommand>(MoveCommand));
    CommandQueue.AddCommand(std::make_shared<ActionCommand>(JumpCommand));

    std::cout << "Pending command count: " << CommandQueue.GetCommandCount() << std::endl;
    CommandQueue.ProcessCommands();

    CommandStack CommandStack;
    CommandStack.AddCommand(std::make_shared<ActionCommand>(AttackCommand));
    CommandStack.AddCommand(std::make_shared<ActionCommand>(AttackCommand));
    CommandStack.AddCommand(std::make_shared<ActionCommand>(JumpCommand));
    CommandStack.AddCommand(std::make_shared<ActionCommand>(MoveCommand));

    std::cout << "Pending command count: " << CommandStack.GetPendingCommandCount() << std::endl;
    CommandStack.ProcessCommands();

    std::cout << "Executed command count: " << CommandStack.GetExecutedCommandCount() << std::endl;
    const size_t ExecutedCommandCount = CommandStack.GetExecutedCommandCount();

    for (size_t i = 0; i < ExecutedCommandCount; ++i)
    {
        CommandStack.UndoLastCommand();
    }
}

void ServiceLocatorTest()
{
    std::shared_ptr<AudioService> Audio = ServiceLocator::GetInstance().ResolveService<AudioService>();
    if (Audio != nullptr)
    {
        Audio->PlaySound("Sound.wav");
    }
    
    ServiceLocator::GetInstance().RegisterService<AudioService>(new AudioService());

    std::shared_ptr<AudioService> Audio1 = ServiceLocator::GetInstance().ResolveService<AudioService>();
    if (Audio1 != nullptr)
    {
        Audio1->PlaySound("Sound.wav");
    }

    std::shared_ptr<AudioService> Audio2 = ServiceLocator::GetInstance().ResolveService<AudioService>();
    if (Audio2 != nullptr)
    {
        Audio2->StopSound("Sound.wav");
    }

    ServiceLocator::GetInstance().UnregisterService<AudioService>();
}

int main(int argc, char* argv[])
{
    // ObjectPoolTest();

    // StateMachineTest();

    // SingletonTest();

    // CommandTest();

    ServiceLocatorTest();
    
    return 0;
}
