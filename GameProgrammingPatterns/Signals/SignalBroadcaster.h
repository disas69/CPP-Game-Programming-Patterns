#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

template <typename Return, typename Arg>
class SignalBroadcaster : public Singleton<SignalBroadcaster<Return, Arg>>
{
    using SignalType = Signal<Arg>;
    using Func = std::function<Return(Arg)>;
    friend Singleton<SignalBroadcaster<Return, Arg>>;

    SignalBroadcaster() = default;

public:
    SignalBroadcaster(const SignalBroadcaster&) = delete;
    SignalBroadcaster& operator=(const SignalBroadcaster&) = delete;

    template <typename SignalType>
    static void AddListener(Func Callback)
    {
        const size_t HashCode = typeid(SignalType).hash_code();
        auto& Instance = SignalBroadcaster<Return, Arg>::GetInstance();
        if (Instance.Signals.find(HashCode) == Instance.Signals.end())
        {
            Instance.Signals[HashCode] = std::vector<Func>();
        }

        Instance.Signals[HashCode].push_back(Callback);
    }

    template <typename SignalType>
    static void Broadcast(const Signal<Arg>& Signal)
    {
        const size_t HashCode = typeid(SignalType).hash_code();
        auto& Instance = SignalBroadcaster<Return, Arg>::GetInstance();
        for (const auto& Callback : Instance.Signals[HashCode])
        {
            if (Callback != nullptr)
            {
                Callback(Signal.GetData());
            }
        }
    }

    template <typename SignalType>
    static void RemoveListeners()
    {
        const size_t HashCode = typeid(SignalType).hash_code();
        SignalBroadcaster<Return, Arg>::GetInstance().Signals.erase(HashCode);
    }

    static void Clear()
    {
        SignalBroadcaster<Return, Arg>::GetInstance().Signals.clear();
    }

private:
    std::unordered_map<size_t, std::vector<Func>> Signals;
};

template <typename Return>
class SignalBroadcaster<Return, void> : public Singleton<SignalBroadcaster<Return, void>>
{
    using SignalType = Signal<void>;
    using Func = std::function<Return()>;
    friend Singleton<SignalBroadcaster<Return, void>>;

    SignalBroadcaster() = default;

public:
    SignalBroadcaster(const SignalBroadcaster&) = delete;
    SignalBroadcaster& operator=(const SignalBroadcaster&) = delete;

    template <typename SignalType>
    static void AddListener(Func Callback)
    {
        const size_t HashCode = typeid(SignalType).hash_code();
        auto& Instance = SignalBroadcaster<Return, void>::GetInstance();
        if (Instance.Signals.find(HashCode) == Instance.Signals.end())
        {
            Instance.Signals[HashCode] = std::vector<Func>();
        }

        Instance.Signals[HashCode].push_back(Callback);
    }

    template <typename SignalType>
    static void Broadcast()
    {
        const size_t HashCode = typeid(SignalType).hash_code();
        auto& Instance = SignalBroadcaster<Return, void>::GetInstance();
        for (const auto& Callback : Instance.Signals[HashCode])
        {
            if (Callback != nullptr)
            {
                Callback();
            }
        }
    }

    template <typename SignalType>
    static void RemoveListeners()
    {
        const size_t HashCode = typeid(SignalType).hash_code();
        SignalBroadcaster<Return, void>::GetInstance().Signals.erase(HashCode);
    }

    static void Clear()
    {
        SignalBroadcaster<Return, void>::GetInstance().Signals.clear();
    }

private:
    std::unordered_map<size_t, std::vector<Func>> Signals;
};