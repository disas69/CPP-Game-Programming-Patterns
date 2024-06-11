#pragma once

#include <unordered_map>
#include <memory>
#include <iostream>
#include "../Singleton/Singleton.h"

class ServiceLocator : public Singleton<ServiceLocator>
{
public:
    ~ServiceLocator() override
    {
        ClearServices();
    }

    template <typename T>
    void RegisterService(T* Service)
    {
        const size_t HashCode = typeid(T).hash_code();
        Services[HashCode] = std::shared_ptr<void>(Service);
        std::cout << "Registered service: " << typeid(T).name() << std::endl;
    }

    template <typename T>
    std::shared_ptr<T> ResolveService()
    {
        const size_t HashCode = typeid(T).hash_code();
        const auto Service = Services.find(HashCode);

        if (Service != Services.end())
        {
            return std::static_pointer_cast<T>(Service->second);
        }

        std::cout << "Service not found: " << typeid(T).name() << std::endl;
        return nullptr;
    }

    template <typename T>
    void UnregisterService()
    {
        const size_t HashCode = typeid(T).hash_code();
        const auto Service = Services.find(HashCode);

        if (Service != Services.end())
        {
            Services.erase(Service);
            std::cout << "Unregistered service: " << typeid(T).name() << std::endl;
        }
        else
        {
            std::cout << "Service not found: " << typeid(T).name() << std::endl;
        }
    }

private:
    std::unordered_map<size_t, std::shared_ptr<void>> Services;

    void ClearServices()
    {
        std::cout << "Clearing services" << std::endl;
        Services.clear();
    }
};
