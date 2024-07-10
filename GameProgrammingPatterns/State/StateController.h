#pragma once

#include <type_traits>
#include <unordered_map>
#include <memory>
#include "State.h"

template <typename T>
class StateController
{
    static_assert(std::is_enum<T>::value, "T must be an enum");
    
public:
    StateController() = default;

    void AddState(T Type, State* StateInstance)
    {
        States[Type] = std::unique_ptr<State>(StateInstance);
    }
    
    T GetCurrentState() const { return CurrentType; }
    
    void SetState(T NewType)
    {
        State* CurrentState = GetState(CurrentType);
        if (CurrentState != nullptr)
        {
            CurrentState->Exit();
        }

        CurrentType = NewType;

        State* NextState = GetState(NewType);
        if (NextState != nullptr)
        {
            NextState->Enter();
        }
    }

    void Update(float DeltaTime)
    {
        State* State = GetState(CurrentType);
        if (State != nullptr)
        {
            State->Update(DeltaTime);
        }
    }

    void HandleInput(InputType Input)
    {
        State* State = GetState(CurrentType);
        if (State != nullptr)
        {
            State->HandleInput(Input);
        }
    }

private:
    T CurrentType;
    std::unordered_map<T, std::unique_ptr<State>> States;

    State* GetState(T State)
    {
        auto It = States.find(State);
        if (It != States.end())
        {
            return It->second.get();
        }

        return nullptr;
    }
};
