#pragma once

template <typename T>
class Singleton
{
public:
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& GetInstance()
    {
        static T Instance;
        return Instance;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};
