# C++ Game Programming Patterns

A collection of the most common game programming patterns written in C++.

- Object Pool
```
  // Create a pool of 3 objects
  ObjectPool<PooledEntity> Pool(3, true);
  
  // Get an object from the pool
  std::shared_ptr<PooledEntity> Entity = Pool.GetObject();
  
  // Return the object to the pool
  Pool.ReturnObject(Entity);
```
- State Machine
```
  // Create a state machine
  StateMachine<State> StateMachine(State::Idle);
  
  // Add transitions
  StateMachine.AddTransition(State::Idle, State::Walking, []() { std::cout << "Start Walking" << std::endl; });
  StateMachine.AddTransition(State::Walking, State::Running, []() { std::cout << "Start Running" << std::endl; });
  
  // Set target state
  StateMachine.SetState(State::Walking);
```
- Singleton
```
  // GameManager is a singleton so GetInstance() returns the same instance
  GameManager::GetInstance().Start();
  GameManager::GetInstance().Update();
  GameManager::GetInstance().Shutdown();
```
- Command
```
  // Create action commands
  auto MoveCommand = std::make_shared<ActionCommand>([]() { std::cout << "Move" << std::endl; }, []() { std::cout << "Undo Move" << std::endl; });
  auto JumpCommand = std::make_shared<ActionCommand>([]() { std::cout << "Jump" << std::endl; }, []() { std::cout << "Undo Jump" << std::endl; });
  
  // Create a command queue and add 2 commands
  CommandQueue CommandQueue;
  CommandQueue.AddCommand(MoveCommand);
  CommandQueue.AddCommand(JumpCommand);
  
  // Process all commands in the queue
  CommandQueue.ProcessCommands();
  
  // Create a command stack and add 3 commands
  CommandStack CommandStack;
  CommandStack.AddCommand(MoveCommand);
  CommandStack.AddCommand(JumpCommand);
  CommandStack.AddCommand(MoveCommand);
  
  // Process all commands in the stack
  CommandStack.ProcessCommands();
  
  // Undo all the commands
  const size_t ExecutedCommandCount = CommandStack.GetExecutedCommandCount();
  for (size_t i = 0; i < ExecutedCommandCount; ++i)
  {
      CommandStack.UndoLastCommand();
  }
```
- ServiceLocator
```
  // Register the audio service
  ServiceLocator::GetInstance().RegisterService<AudioService>(new AudioService());
  
  // Resolve the audio service and play a sound
  std::shared_ptr<AudioService> Audio1 = ServiceLocator::GetInstance().ResolveService<AudioService>();
  if (Audio1 != nullptr)
  {
      Audio1->PlaySound("Sound.wav");
  }
  
  // Unregister the audio service
  ServiceLocator::GetInstance().UnregisterService<AudioService>();
```
- Signals
```
  // Add a listener to the Trigger Signal with no parameters
  SignalBroadcaster<void, void>::AddListener<TriggerSignal>([]()
  {
      std::cout << "Trigger Received" << std::endl;
  });

  // Broadcast the Trigger Signal
  SignalBroadcaster<void, void>::Broadcast<TriggerSignal>();

  // Remove all listeners
  SignalBroadcaster<void, void>::RemoveListeners<TriggerSignal>();

  // Add a listener to the Collision Signal with a boolean parameter
  SignalBroadcaster<void, bool>::AddListener<CollisionSignal>([](bool Value)
  {
      std::cout << "Collision Received: " << Value << std::endl;
  });

  // Broadcast the Collision Signal
  SignalBroadcaster<void, bool>::Broadcast<CollisionSignal>(true);

  // Remove all listeners
  SignalBroadcaster<void, bool>::RemoveListeners<CollisionSignal>();
```
- EventQueue
```
  // Create an event queue
  EventQueue EventQueue;

  // Add 3 audio events
  EventQueue.AddEvent(std::make_unique<AudioEvent>(1));
  EventQueue.AddEvent(std::make_unique<AudioEvent>(2));
  EventQueue.AddEvent(std::make_unique<AudioEvent>(3));

  // Process all events in the queue at a later time
  EventQueue.ProcessEvents();
```
