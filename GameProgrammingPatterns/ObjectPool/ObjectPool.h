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
    ObjectPool(T* ObjectTemplate, size_t InitialSize)
    {
        for (size_t i = 0; i < InitialSize; ++i)
        {
            std::shared_ptr<T> Object = std::make_shared<T>(*ObjectTemplate);
            Object->Initialize();
            Pool.push(Object);
        }
    }
    
    ObjectPool(size_t InitialSize)
    {
        for (size_t i = 0; i < InitialSize; ++i)
        {
            std::shared_ptr<T> Object = std::make_shared<T>();
            Object->Initialize();
            Pool.push(Object);
        }
    }

    ~ObjectPool()
    {
        while (!Pool.empty())
        {
            Pool.front()->Release();
            Pool.pop();
        }
    }

    size_t GetSize() const { return Pool.size(); }

    std::shared_ptr<T> GetObject()
    {
        if (Pool.empty())
        {
            std::cout << "Pool is empty, creating new object" << std::endl;
            std::shared_ptr<T> Object = std::make_shared<T>();
            Object->Initialize();
            return Object;
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
    std::queue<std::shared_ptr<T>> Pool;
};