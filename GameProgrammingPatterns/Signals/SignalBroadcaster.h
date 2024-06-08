#pragma once

#include <map>
#include <vector>
#include <memory>
#include <functional>

template <typename T, typename DataType>
class SignalBroadcaster
{
    typedef std::function<void(DataType)> Func;
    
public:
    void AddListener(std::shared_ptr<T> Signal, Func Listener)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        if (Signals.find(HashCode) == Signals.end())
        {
            Signals[HashCode] = std::vector<Func>();
        }
        
        Signals[HashCode].push_back(Listener);
    }

    void RemoveListener(std::shared_ptr<T> Signal, Func Listener)
    {
        const size_t HashCode = typeid(Signal).hash_code();

        auto& Listeners = Signals[HashCode];
        Listeners.erase(std::remove(Listeners.begin(), Listeners.end(), Listener), Listeners.end());

        if (Signals[HashCode].empty())
        {
            Signals.erase(HashCode);
        }
    }

    void RemoveListeners(std::shared_ptr<T> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        Signals.erase(HashCode);
    }

    void Broadcast(std::shared_ptr<T> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();

        for (const auto& Listener : Signals[HashCode])
        {
            Listener(Signal->GetData());
        }
    }

private:
    std::map<size_t, std::vector<Func>> Signals;
};

template <typename T>
class SignalBroadcaster<T, void>
{
    typedef std::function<void()> Func;

public:
    void AddListener(std::shared_ptr<T> Signal, Func Listener)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        if (Signals.find(HashCode) == Signals.end())
        {
            Signals[HashCode] = std::vector<Func>();
        }

        Signals[HashCode].push_back(Listener);
    }

    void RemoveListener(std::shared_ptr<T> Signal, Func Listener)
    {
        const size_t HashCode = typeid(Signal).hash_code();

        auto& Listeners = Signals[HashCode];
        Listeners.erase(std::remove(Listeners.begin(), Listeners.end(), Listener), Listeners.end());

        if (Listeners.empty())
        {
            Signals.erase(HashCode);
        }
    }

    void RemoveListeners(std::shared_ptr<T> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        Signals.erase(HashCode);
    }

    void Broadcast(std::shared_ptr<T> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();

        for (const auto& Listener : Signals[HashCode])
        {
            Listener();
        }
    }

private:
    std::map<size_t, std::vector<Func>> Signals;
};