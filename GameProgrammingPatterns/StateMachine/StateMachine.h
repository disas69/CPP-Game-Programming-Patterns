#pragma once

#include <functional>
#include <map>

template <typename T>
class StateMachine
{
    static_assert(std::is_enum<T>::value, "T must be an enum");
public:
    StateMachine(T InitialState) : CurrentState(InitialState) {}

    void AddTransition(T From, T To, std::function<void()> Transition)
    {
        for (const auto& TransitionPair : TransitionsMap)
        {
            if (TransitionPair.first.first == From && TransitionPair.first.second == To)
            {
                return;
            }
        }

        TransitionsMap[std::make_pair(From, To)] = Transition;
    }

    void SetState(T NewState)
    {
        for (const auto& TransitionPair : TransitionsMap)
        {
            if (TransitionPair.first.first == CurrentState && TransitionPair.first.second == NewState)
            {
                TransitionPair.second();
                break;
            }
        }

        CurrentState = NewState;
    }

    T GetCurrentState() const { return CurrentState; }
    bool IsInState(T State) const { return CurrentState == State; }

private:
    T CurrentState;
    std::map<std::pair<T, T>, std::function<void()>> TransitionsMap;
};
