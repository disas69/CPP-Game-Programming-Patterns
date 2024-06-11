#pragma once

#include <iostream>
#include <memory>
#include <queue>

class PooledObject;

template <typename T>
class ObjectPool
{
    static_assert(std::is_base_of<PooledObject, T>::value, "T must be a PooledObject");

public:
    ObjectPool(size_t InitialSize, bool AutoExpand = false) : AutoExpand(AutoExpand)
    {
        try
        {
            for (size_t i = 0; i < InitialSize; ++i)
            {
                std::shared_ptr<T> Object = std::make_shared<T>();
                Object->Initialize();
                Pool.push(Object);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception during pool initialization: " << e.what() << std::endl;
        }
    }

    ObjectPool(size_t InitialSize, std::function<std::shared_ptr<T>()> Factory, bool AutoExpand = false) : AutoExpand(AutoExpand)
    {
        try
        {
            for (size_t i = 0; i < InitialSize; ++i)
            {
                std::shared_ptr<T> Object = Factory();
                Object->Initialize();
                Pool.push(Object);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception during pool initialization: " << e.what() << std::endl;
        }
    }

    ~ObjectPool()
    {
        while (!Pool.empty())
        {
            Pool.pop();
        }
    }

    size_t GetSize() const { return Pool.size(); }

    std::shared_ptr<T> GetObject()
    {
        if (Pool.empty())
        {
            if (AutoExpand)
            {
                std::cout << "Pool is empty, creating new object" << std::endl;
                std::shared_ptr<T> Object = std::make_shared<T>();
                Object->Initialize();
                return Object;
            }
            else
            {
                throw std::runtime_error("Pool is empty and cannot expand further");
            }
        }

        std::cout << "Getting object from pool" << std::endl;
        std::shared_ptr<T> Object = Pool.front();
        Pool.pop();
        Object->Reset();
        return Object;
    }

    void ReturnObject(std::shared_ptr<T> Object)
    {
        std::cout << "Returning object to pool" << std::endl;
        Pool.push(Object);
    }

private:
    bool AutoExpand = false;
    std::queue<std::shared_ptr<T>> Pool;
};
