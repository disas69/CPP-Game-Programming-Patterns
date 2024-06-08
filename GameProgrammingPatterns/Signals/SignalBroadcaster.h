#pragma once

#include <map>
#include <vector>
#include <memory>
#include <functional>
#include "Signal.h"

template <typename ReturnType, typename DataType>
class SignalBroadcaster
{
    typedef std::function<ReturnType(DataType)> GenericFunc;
    
public:
    void AddListener(std::shared_ptr<Signal<DataType>> Signal, GenericFunc Listener)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        if (Signals.find(HashCode) == Signals.end())
        {
            Signals[HashCode] = std::vector<GenericFunc>();
        }
        
        Signals[HashCode].push_back(Listener);
    }

    void RemoveListener(std::shared_ptr<Signal<DataType>> Signal, GenericFunc Listener)
    {
        const size_t HashCode = typeid(Signal).hash_code();

        auto First = Signals[HashCode].begin();
        const auto It = std::remove(First, Signals[HashCode].end(), Listener);
        Signals[HashCode].erase(It, Signals[HashCode].end());

        if (Signals[HashCode].empty())
        {
            Signals.erase(HashCode);
        }
    }

    void RemoveListeners(std::shared_ptr<Signal<DataType>> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        Signals.erase(HashCode);
    }

    void Broadcast(std::shared_ptr<Signal<DataType>> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();

        for (const auto& Listener : Signals[HashCode])
        {
            Listener(Signal->GetData());
        }
    }

private:
    std::map<size_t, std::vector<GenericFunc>> Signals;
};

template <>
class SignalBroadcaster<void, void>
{
    typedef std::function<void()> VoidFunc;
public:
    void AddListener(std::shared_ptr<Signal<void>> Signal, VoidFunc Listener)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        if (Signals.find(HashCode) == Signals.end())
        {
            Signals[HashCode] = std::vector<VoidFunc>();
        }
        
        Signals[HashCode].push_back(Listener);
    }

    void RemoveListeners(std::shared_ptr<Signal<void>> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();
        Signals.erase(HashCode);
    }

    void Broadcast(std::shared_ptr<Signal<void>> Signal)
    {
        const size_t HashCode = typeid(Signal).hash_code();

        for (const auto& Listener : Signals[HashCode])
        {
            Listener();
        }
    }

private:
    std::map<size_t, std::vector<VoidFunc>> Signals;
};
