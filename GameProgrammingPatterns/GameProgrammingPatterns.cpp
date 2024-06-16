#include <iostream>
#include <vector>
#include <memory>

#include "Command/ActionCommand.h"
#include "Command/CommandQueue.h"
#include "Command/CommandStack.h"
#include "EventQueue/AudioEvent.h"
#include "EventQueue/EventQueue.h"
#include "ObjectPool/ObjectPool.h"
#include "ObjectPool/PooledEntity.h"
#include "ServiceLocator/AudioService.h"
#include "ServiceLocator/ServiceLocator.h"
#include "Signals/CollisionSignal.h"
#include "Signals/SignalBroadcaster.h"
#include "Signals/TriggerSignal.h"
#include "Singleton/GameManager.h"
#include "StateMachine/StateMachine.h"

void ObjectPoolTest()
{
    // Create a pool of 3 objects
    ObjectPool<PooledEntity> Pool(3, true);

    std::vector<std::shared_ptr<PooledEntity>> Entities;

    // Get 5 objects from the pool, so 2 objects will be created
    for (size_t i = 0; i < 5; ++i)
    {
        std::shared_ptr<PooledEntity> Entity = Pool.GetObject();
        Entity->SetPosition(i, i * 2);

        std::cout << "Entity position: " << Entity->GetXPosition() << ", " << Entity->GetYPosition() << std::endl;
        Entities.push_back(Entity);
    }

    // Return all objects to the pool
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

    // Create a state machine with 3 states and add transitions between them
    StateMachine<State> StateMachine(State::Idle);
    
    StateMachine.AddTransition(State::Idle, State::Walking, []() { std::cout << "Start Walking" << std::endl; });
    StateMachine.AddTransition(State::Walking, State::Running, []() { std::cout << "Start Running" << std::endl; });
    StateMachine.AddTransition(State::Running, State::Idle, []() { std::cout << "Start Idle" << std::endl; });

    // Set target state and execute transitions
    StateMachine.SetState(State::Walking);
    StateMachine.SetState(State::Running);
    StateMachine.SetState(State::Idle);
}

void SingletonTest()
{
    // GameManager is a singleton so GetInstance() returns the same instance
    GameManager::GetInstance().Start();
    GameManager::GetInstance().Update();
    GameManager::GetInstance().Shutdown();
}

void CommandTest()
{
    // Create 3 action commands with execute and undo functions
    auto MoveCommand = std::make_shared<ActionCommand>([]() { std::cout << "Move" << std::endl; }, []() { std::cout << "Undo Move" << std::endl; });
    auto JumpCommand = std::make_shared<ActionCommand>([]() { std::cout << "Jump" << std::endl; }, []() { std::cout << "Undo Jump" << std::endl; });
    auto AttackCommand = std::make_shared<ActionCommand>([]() { std::cout << "Attack" << std::endl; }, []() { std::cout << "Undo Attack" << std::endl; });

    // Create a command queue and add 2 commands
    CommandQueue CommandQueue;
    CommandQueue.AddCommand(MoveCommand);
    CommandQueue.AddCommand(JumpCommand);

    // Process all commands in the queue
    std::cout << "Pending command count: " << CommandQueue.GetCommandCount() << std::endl;
    CommandQueue.ProcessCommands();

    // Create a command stack and add 4 commands
    CommandStack CommandStack;
    CommandStack.AddCommand(AttackCommand);
    CommandStack.AddCommand(AttackCommand);
    CommandStack.AddCommand(JumpCommand);
    CommandStack.AddCommand(MoveCommand);

    // Process all commands in the stack
    std::cout << "Pending command count: " << CommandStack.GetPendingCommandCount() << std::endl;
    CommandStack.ProcessCommands();

    std::cout << "Executed command count: " << CommandStack.GetExecutedCommandCount() << std::endl;
    const size_t ExecutedCommandCount = CommandStack.GetExecutedCommandCount();

    // Undo all the executed commands
    for (size_t i = 0; i < ExecutedCommandCount; ++i)
    {
        CommandStack.UndoLastCommand();
    }
}

void ServiceLocatorTest()
{
    // Try to resolve the audio service, it will return nullptr because it's not yet registered
    std::shared_ptr<AudioService> Audio = ServiceLocator::GetInstance().ResolveService<AudioService>();
    if (Audio != nullptr)
    {
        Audio->PlaySound("Sound.wav");
    }

    // Register the audio service
    ServiceLocator::GetInstance().RegisterService<AudioService>(new AudioService());

    // Resolve the audio service and play a sound
    std::shared_ptr<AudioService> Audio1 = ServiceLocator::GetInstance().ResolveService<AudioService>();
    if (Audio1 != nullptr)
    {
        Audio1->PlaySound("Sound.wav");
    }

    // Resolve the audio service again and stop the sound
    std::shared_ptr<AudioService> Audio2 = ServiceLocator::GetInstance().ResolveService<AudioService>();
    if (Audio2 != nullptr)
    {
        Audio2->StopSound("Sound.wav");
    }

    // Unregister the audio service
    ServiceLocator::GetInstance().UnregisterService<AudioService>();
}

// Define the static Signals member if SignalBroadcaster is not a singleton
// std::unordered_map<size_t, std::vector<SignalBroadcaster::Func>> SignalBroadcaster::Signals;

void SignalsTest()
{
    // Add a listener to the trigger signal
    SignalBroadcaster<void, void>::AddListener<TriggerSignal>([]()
    {
        std::cout << "Trigger Received" << std::endl;
    });

    // Broadcast the trigger signal and remove all listeners
    SignalBroadcaster<void, void>::Broadcast<TriggerSignal>();
    SignalBroadcaster<void, void>::RemoveListeners<TriggerSignal>();

    // Add a listener to the collision signal
    SignalBroadcaster<void, bool>::AddListener<CollisionSignal>([](bool Value)
    {
        std::cout << "Collision Received: " << Value << std::endl;
    });

    // Broadcast the collision signal and remove all listeners
    SignalBroadcaster<void, bool>::Broadcast<CollisionSignal>(true);
    SignalBroadcaster<void, bool>::RemoveListeners<CollisionSignal>();
}

void EventQueueTest()
{
    // Create an event queue and add 3 audio events
    EventQueue EventQueue;
    EventQueue.AddEvent(std::make_unique<AudioEvent>(1));
    EventQueue.AddEvent(std::make_unique<AudioEvent>(1));
    EventQueue.AddEvent(std::make_unique<AudioEvent>(2));

    // Process all events in the queue
    EventQueue.ProcessEvents();
}

int main(int argc, char* argv[])
{
    // ObjectPoolTest();

    // StateMachineTest();

    // SingletonTest();

    // CommandTest();

    // ServiceLocatorTest();

    // SignalsTest();

    EventQueueTest();
    
    return 0;
}
