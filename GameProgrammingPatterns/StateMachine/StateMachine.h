#pragma once

#include <functional>
#include <unordered_map>

template <typename T>
class StateMachine
{
    static_assert(std::is_enum<T>::value, "T must be an enum");

public:
    StateMachine(T InitialState) : CurrentState(InitialState) {}
    ~StateMachine() = default;

    void AddTransition(T From, T To, std::function<void()> Transition)
    {
        TransitionsMap[From][To] = Transition;
    }

    bool SetState(T NewState)
    {
        auto ItFrom = TransitionsMap.find(CurrentState);
        if (ItFrom != TransitionsMap.end())
        {
            auto ItTo = ItFrom->second.find(NewState);
            if (ItTo != ItFrom->second.end())
            {
                ItTo->second();
                CurrentState = NewState;
                return true;
            }
        }

        return false;
    }

    T GetCurrentState() const { return CurrentState; }
    bool IsInState(T State) const { return CurrentState == State; }

private:
    T CurrentState;
    std::unordered_map<T, std::unordered_map<T, std::function<void()>>> TransitionsMap;
};
