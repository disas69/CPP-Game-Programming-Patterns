#pragma once

template <typename T>
class Signal
{
public:
    Signal(T Data) : Data(Data) {}
    virtual ~Signal() = default;

    T GetData() const
    {
        return Data;
    }

private:
    T Data;
};

template <>
class Signal<void>
{
public:
    Signal() = default;
    virtual ~Signal() = default;
};
